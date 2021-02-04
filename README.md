# 星云平台桌面客户端

## 安装

1. Qt 5.15.2
2. MySQL 5.7
3. MySQL Workbench 5.7

## 导入测试数据库

将本项目的test.sql导入数据库中

1. 使用MySQL Workbench，登录

   ![](https://github.com/lyxiong0/xingyun-client/blob/main/images/login.png)

2. 选择Data Import/Restore

   ![](https://github.com/lyxiong0/xingyun-client/blob/main/images/import.png)

3. 选择Import from Self --> Start Import

   ![](https://github.com/lyxiong0/xingyun-client/blob/main/images/import2.png)

## Windows编译报错

如果控制台出现错误提示`QSqlDatabase: QMYSQL driver not loaded`，采用以下步骤解决

1. 从 `[MySQL安装目录]\lib` 中将 `libmysql.dll` 文件复制 `[Qt安装目录]\5.15.2\mingw81_64\bin` 中。其中5.6、49_32可能因为qt和mingw版本不同文件夹名有所变化。
2. 将本项目文件夹`sqldrivers`复制到`[Qt安装目录]\5.15.2\mingw81_64\plugins\`
3. 若仍然无效，按照https://blog.csdn.net/zxl_1996/article/details/104299715自行编译Qt对应版本的驱动

