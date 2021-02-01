# 星云平台桌面客户端

## 安装

1. Qt 6.0
2. MySQL 8.0
3. MySQL Workbench 8.0

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

1. 从 `[MySQL安装目录]\lib` 中将 `libmysql.dll` 文件复制 `[Qt安装目录]\Qt5.6.1\5.6\mingw49_32\bin` 中。其中5.6、49_32可能因为qt和mingw版本不同文件夹名有所变化。
2. 将本项目文件夹`sqldrivers`复制到`[Qt安装目录]\Qt5.6.1\5.6\mingw49_32\plugins\`

