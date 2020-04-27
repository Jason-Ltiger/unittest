/**
 * Copyright(C) 2016 ROKAE. All Rights Reserved.
 * Information in this file is the intellectual property of ROKAE, and may
 * contains trade secrets that must be stored and viewed confidentially.
 *
 * @file db_interface.hpp
 * @author changfeng
 * @date Sep 19, 2016
 * @brief 定义数据库接口操作类需要实现的基本功能
 */

#ifndef DAO_DB_INTERFACE_HPP_
#define DAO_DB_INTERFACE_HPP_

#include <string>
#include <vector>

///定义数据库操作的错误码
enum DBError {
    DBERROR_NONE_ERROR = 0, ///< 无错误
    DBERROR_OPEN_DB_FAILED, ///< DB打开失败
    DBERROR_NO_DB_FILE, ///< 没有DB文件
    DBERROR_DAO_NULL, ///< 无效的数据库操作对象
    DBERROR_BAD_ALLOC, ///< 申请空间失败
    DBERROR_BAD_PARAM, ///< 错误的参数
    DBERROR_WRONG_RESULT, ///< 执行出错
    DBERROR_EXEC_SQL_FAILED, ///< 执行SQL语句失败
};

///控制器的命名空间
namespace rc {

///提供数据库文件进行管理的操作接口
namespace db {

///进行数据库遍历操作时可能需要的回调处理函数的类型定义
typedef int (*SQLCallBack)(void*, int, char**, char**);

/**
 * @brief 数据库接口的纯虚基类，此类定义了数据库接口操作类需要实现的基本功能
 */
class DBInterface {
    public:

        /**
         * @brief 构造函数
         */
        DBInterface() {};

        /**
         * @brief 析构函数
         */
        virtual ~DBInterface() {};

        /**
         * @brief 赋值拷贝函数
         * @attention 禁用赋值拷贝
         */
        DBInterface& operator=(const DBInterface &rhs) = delete;

        /**
         * @brief 拷贝构造函数
         * @attention 禁用拷贝构造
         */
        DBInterface(const DBInterface &other) = delete;

        /**
         * @brief  打开一个数据库文件
         * @param  DBName 所需打开的数据库的路径
         * @return 0-执行成功,其他-失败
         */
        virtual int OpenDB(const std::string &DBName) = 0;

        /**
         * @brief 关闭当前打开的数据库
         */
        virtual void CloseDB() = 0;

        /**
         * @brief　获取数据库的连接状态
         * @return true:当前存在有效的数据连接
         *         false:当前不存在有效的数据连接
         */
        virtual bool IsDBConnected() = 0;

        /**
         * @brief  获取当前连接的数据库的名字
         * @return 当前连接的数据库的名字
         */
        virtual std::string GetConnectedDBName() = 0;

        /**
         * @brief 开始启动事务
         * @return 0-执行成功,其他-失败
         */
        virtual int BeginTransaction() = 0;

        /**
         * @brief  提交事务
         * @return 0-执行成功,其他-失败
         */
        virtual int CommitTransaction() = 0;

        /**
         * @brief 回滚事务
         * @return 0-执行成功,其他-失败
         */
        virtual int RollbackTransaction() = 0;

        /**
         * @brief  执行SQL语句
         *         执行可以通过sqlite3_exec执行的语句，包括insert、update、delete、select等
         * @param  SQLCommand 要执行的sql语句
         * @param  callback 执行select语句时的回调函数，对于insert、update、delete等没有返回数据的sql命令此处为NULL
         * @param  argv 执行的回调函数的传入参数，对于insert、update、delete等没有返回数据的sql命令此处为NULL
         * @param  transaction_flag 决定是否立即执行事物提交，默认值为false
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int ExecSql(const std::string &SQLCommand, SQLCallBack callback, void *argv,
                bool transaction_flag = false) = 0;

        /**
         * @brief  执行SQL语句
         *         执行执行的SQL语句，包括insert、update、delete、select等
         * @param  SQLCommand 要执行的sql语句
         * @param  callback 执行select语句时的回调函数，对于insert、update、delete等没有返回数据的sql命令此处为NULL
         * @param  argv 执行的回调函数的传入参数，对于insert、update、delete等没有返回数据的sql命令此处为NULL
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int ExecSQLCommand(const std::string &SQLCommand, SQLCallBack callback, void *argv) = 0;

        /**
         * @brief  执行一条SQL语句
         *         执行不需要回调的SQL语句，包括insert、update、delete等
         * @param  SQLCommand 要执行的sql语句
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int ExecSQLCommand(const std::string &SQLCommand) = 0;

        /**
         * @brief  执行一组事务
         * @param  SQLTrans 执行的事务命令集，以vector的形式存储每一条命令
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int ExecTransaction(const std::vector<std::string> &SQLTrans) = 0;

        /**
         * @brief  向表中插入一列数据记录
         * @param  tableName 所需插入的表的名称
         * @param  fieldsNames 容纳表中各字段的vector
         * @param  targetValues 容纳所需插入的值的vector
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int InsertRecord(const std::string &tableName, const std::vector<std::string> &fieldsNames,
                const std::vector<std::string> &targetValues) = 0;

        /**
         * @brief 替换/插入一条记录
         * @param tableName 指定表的名称
         * @param fieldsNames 指定的记录的所有字段
         * @param targetValues 指定记录的所有取值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int ReplaceRecord(const std::string &tableName, const std::vector<std::string> &fieldsNames,
                const std::vector<std::string> &targetValues) = 0;

        /**
         * @brief  删除制定表中一条记录,根据指定的id进行删除操作
         * @param  tableName 指定表的名称
         * @param  id 指定的id编号
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int DeleteRecord(const std::string &tableName, const int id) = 0;

        /**
         * @brief  删除制定表中一条记录,根据匹配的条件进行删除
         * @param  tableName 指定表的名称
         * @param  fieldsName 指定的字段名
         * @param  targetValue 与制定字段名匹配的值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int DeleteRecord(const std::string &tableName, const std::string &fieldsName,
                const std::string &targetValue) = 0;

        /**
         * @brief  更新数据库中的一条记录的所有值,根据匹配的条件进行更新
         * @param  tableName 指定表的名称
         * @param  condition_fields 条件字段
         * @param  condition_value  条件值
         * @param  fieldsNames  指定的记录的所有字段
         * @param  targetValues 指定记录的所有取值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int UpdateRecord(const std::string &tableName,
                const std::string &condition_fields,
                const std::string &condition_value,
                const std::vector<std::string> &fieldsNames,
                const std::vector<std::string> &targetValues) = 0;

        /**
         * @brief  更新数据库中的一条记录的某一项值
         * @param  tableName 制定表的名称
         * @param  fieldsName 指定的字段名
         * @param  value 指定的更新值
         * @param  id 记录的id值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int UpdateRecordValue(const std::string &tableName, const std::string &fieldsName,
                const std::string &value, const int id) = 0;

        /**
         * @brief  按行遍历数据表中的记录，每遍历一行，对当前行执行一次回调处理
         * @param  tableName 指定的表的名称
         * @param  callback 执行回调处理的回调函数\n
         *         回调函数返回0将继续执行遍历，否则将中断遍历操作
         * @param  argv 向回调函数传递的参数
         * @param  id 指定的id值,默认值为0
         * @note   id为0时,对表中的所有记录遍历
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int TraversalRecordbyRow(const std::string &tableName, SQLCallBack callback,
                 void *argv, int id = 0) = 0;

        /**
         * @brief  按列遍历数据库中的记录，每遍历一行，对当前行执行一次回调处理
         * @param  tableName 指定的表的名称
         * @param  fieldsName 需要被遍历的字段列
         * @param  callback 执行回调处理的回调函数
         *         回调函数返回0将继续执行遍历，否则将中断遍历操作
         * @param  argv 向回调函数传递的参数
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int TraversalRecordbyColumn(const std::string &tableName, const std::string &fieldsName,
                 SQLCallBack callback, void *argv) = 0;

        /**
         * @brief  获取select返回的第一个行第一列的结果
         * @param  SQLCommand 执行的select语句
         * @param  &result 输出，返回的int型数据结果值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int GetResultData(const std::string &SQLCommand, int        &result) = 0;

        /**
         * @brief  获取select返回的第一个行第一列的结果
         * @param  SQLCommand 执行的select语句
         * @param  &result 输出，返回的double型数据结果值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int GetResultData(const std::string &SQLCommand, double     &result) = 0;

        /**
         * @brief  获取select返回的第一个行第一列的结果
         * @param  SQLCommand 执行的select语句
         * @param  &result 输出，返回的string型数据结果值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int GetResultData(const std::string &SQLCommand, std::string &result) = 0;

        /**
         * @brief  以表单形式获取符合匹配条件的所有记录
         * @param  tableName 指定的表的名字
         * @param  dbResult 输出,最终获得的表单
         * @param  &nRow 输出,获得的表单的列数
         * @param  &nCol 输出,获得的表单的行数
         * @param  fieldsName 匹配条件中的字段
         * @param  targetValue 匹配条件中的值
         * @return 操作结果，成功返回0，否则返回错误码
         */
        virtual int GetTable(const std::string &tableName, char **dbResult, int &nRow,
                int &nCol, const std::string &fieldsName = "", const std::string &targetValue = "") = 0;

        /**
         * @brief 释放GetTable申请到的表单
         * @note  与GetTable配套使用
         */
        virtual void FreeTable(char **dbResult) = 0;

        /**
         * @brief  获取指定表的id最大值
         * @param  tableName 指定的表名
         * @return 指定表的最大id值
         */
        virtual int GetMaxID(const std::string &tableName) = 0;

        /**
         * @brief  获取指定表的指定记录条数
         * @param  tableName 指定的表名
         * @param  fieldsName 指定的字段名,默认为空串
         * @param  targetValue 指定的字段值,默认为空串
         * @return 指定表中包含的记录的数量
         */
        virtual int GetRecordCount(const std::string &tableName, const std::string &fieldsName = "",
                const std::string &targetValue = "") = 0;

        /**
         * @brief  判断某个表在当前打开的数据库中是否存在
         * @param  tableName 所需判断的表的名称
         * @return true:数据库中存在指定的表
         *         false:数据库中不存在指定的表或数据库发生了错误
         */
        virtual bool TestTableExist(const std::string &tableName) = 0;

}; /* class DBInterface */

} /* namespace db */

} /* namespcae rc */

#endif /* DAO_DB_INTERFACE_HPP_ */
