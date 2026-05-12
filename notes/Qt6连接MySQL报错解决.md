# Qt6 连接 MySQL 数据库系列问题解决指南

在 Qt6 中连接 MySQL 数据库时，常会遇到各种相关问题。以下是针对“构建数据库驱动、找不到驱动、无法连接远程数据库”等连续性问题的完整解决步骤：

## 1. 基础配置
在 `.pro` 文件中，必须包含 `sql` 模块：
```pro
QT += widgets network sql
```
代码中打开数据库失败时，一定要输出底层的真实错误原因以供排查：
```cpp
qDebug() << "数据库连接失败，原因: " << m_db.lastError().text();
```

## 2. 解决 "Driver not loaded" 问题
Qt6 官方不再预先提供 `qsqlmysql.dll`，我们需要自行进行编译

### 2.1 准备所需的开发库
下载安装好MySQL后，进入安装目录下(`C:\Program Files\MySQL\MySQL Server 8.0`)的 `lib` 和 `include` 目录，分别复制出这两个目录的绝对路径备用。 

### 2.2 编译 MySQL 驱动插件
1. 打开 Qt Creator，选择 **“文件” -> “打开文件或项目”**，找到 Qt 安装目录中的源码项目：
   文件路径：`盘符:\Qt\6.8.3\Src\qtbase\src\plugins\sqldrivers\CMakeLists.txt`  
   如果没有Src文件夹，请使用Qt maintenance工具添加source。
   
2. 配置项目时选择您当前的编译器（如 MinGW 64-bit）。
3. 在 CMake 配置（可以在 Initial或 Configuration 中）加上这三个关键变量：
   - `MySQL_INCLUDE_DIR` = 填入刚才复制出来的 `include` 目录的绝对路径
   - `MySQL_LIBRARY` = 填入刚才复制出来的 `lib` 目录下的 `libmysql.lib` 文件绝对路径
   - `FEATURE_sql_mysql` = `ON`
4. 运行 CMake 配置，并在底部的**概要信息 (General Messages)**窗口中确认有输出：`MySQL .................. yes`。
5. 确认无误后点击左下角的小锤子**构建**。
6. 构建成功后，在生成目录（如 `build/.../plugins/sqldrivers/`）下找到 **`qsqlmysql.dll`**。将其放入当前 Qt 环境的插件驱动中：`盘符:\Qt\6.8.3\mingw_64\plugins\sqldrivers\`。

### 2.3 补齐动态库依赖
将步骤 2.1 中的 `lib` 目录里的几个核心 DLL 拷贝到您的 **程序运行输出目录（和您的 `.exe` 程序位于同个目录）**。通常需要：
- `libmysql.dll`
- `libcrypto-1_1-x64.dll` (若有)
- `libssl-1_1-x64.dll` (若有)

## 3. 解决 "Access denied for user 'root'" 问题(远程访问权限问题)
当您填入正确的账号和密码，并且连接远程虚拟机环境内的数据库出现拒绝访问错误时，这一般是 MySQL 默认的安全机制（只允许本地 127.0.0.1 登录）引起的。  

先启动服务，power shell 以管理员身份运行：  
net start mysql80  

通过虚拟机本地终端登入 MySQL 命令行，依次执行并开放远程访问权限：
```sql
-- 将 root 账户的访问权限放开给全部 IP
UPDATE mysql.user SET Host='%' WHERE User='root';

-- 刷新权限，立刻生效
FLUSH PRIVILEGES;

-- 退出
EXIT;
```
配置完成后回到 Qt 重新运行，便能顺利连上您的数据库了！
