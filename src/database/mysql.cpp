//
// Created by chanbin on 25. 3. 4.
//

#include "mysql.h" // mysql Class의 인터페이스임 DB 관련

// mysql class database connect
// 인자로 호스트, db이름, 유저이름, 비번, 포트를 받음
void Mysql::connect(std::string &host, std::string& dbname, std::string &user, std::string &password, int port) :
host(host), dbname(dbname), user(user), password(password), port(port), isConnect(false)
{
    try
    {
        // mysql session setting
        session = std::make_unique<mysqlx::Session>
        (host, port, user, password);

        // database에 연결 성공할 시 true로 전환
        isConnect = true;
    }
    catch (mysqlx::Error &err)
    {
        // 에러가 발생하였을 때 에러 출력하게 함
        std::cerr << "connect error: " << err.what() << std::endl;
    }
}

// insert 역할 하는 쿼리임
QueryResult Mysql::insertQuery(std::string &sql) const
{
    // 결과를 반환할 Qresult를 생성
    QueryResult Qresult;

    try
    {
        // 설정한 dbName으로 설정
        mysqlx::Schema schema = session->getSchema(dbname);

        // 인자로 받은 sql을 실행
        session->sql(sql).execute();

        // insert에 성공하였을 시 true로 변환
        Qresult.success = true;
    }
    catch (const mysqlx::Error& err)
    {
        // Error message를 담아서 리턴함
        std::string ErrorString = std::format(
         "InsertQuery Error: ",
             err.what()
         );

        Qresult.errorMessage = ErrorString;
        std::cerr << ErrorString << std::endl;
    }

    return Qresult;
};


// select 역할 하는 쿼리임
QueryResult Mysql::selectQuery(std::string &sql) const
{
    // 결과를 반환할 Qresult를 생성
    QueryResult Qresult;

    try
    {
        // 설정한 dbName으로 설정
        mysqlx::Schema schema = session->getSchema(dbname);

        // 인자로 받은 sql을 실행
        auto result = session->sql(sql).execute();

        // mysql 행을 생성
        mysqlx::Row row;

        while ((row = result.fetchOne())) // 마지막 행이 나올 때 까지 무한 반복함
        {
            // 행 안의 열마다 반복 하게 함
            for (auto childRow : row)
            {
                // 쿼리 결과 구조체에 데이터를 삽입함
                Qresult.rows.push_back({childRow->first, childRow->second});
            }
        }

        // insert에 성공하였을 시 true로 변환 함
        Qresult.success = true;
    }
    catch (const mysqlx::Error& err)
    {
        // Error message를 담아서 리턴함
        std::string ErrorString = std::format(
         "SelectQuery Error: ",
             err.what()
         );

        Qresult.errorMessage = ErrorString;
        std::cerr << ErrorString << std::endl;
    }

    return Qresult;
};


// update 역할 하는 쿼리임
QueryResult Mysql::updateQuery(std::string &sql) const
{
    // 결과를 반환할 Qresult를 생성
    QueryResult Qresult;

    try
    {
        // 설정한 dbName으로 설정
        mysqlx::Schema schema = session->getSchema(dbname);

        // 인자로 받은 sql을 실행
        session->sql(sql).execute();

        // insert에 성공하였을 시 true로 변환 함
        Qresult.success = true;
    }
    catch (const mysqlx::Error& err)
    {
        // Error message를 담아서 리턴함
        std::string ErrorString = std::format(
        "UpdateQuery Error: ",
            err.what()
        );

        Qresult.errorMessage = ErrorString;
        std::cerr << ErrorString << std::endl;
    }

    return Qresult;
};


// delete 역할 하는 쿼리임
QueryResult Mysql::deleteQuery(std::string &sql) const
{
    // 결과를 반환할 Qresult를 생성
    QueryResult Qresult;

    try
    {
        // 설정한 dbName으로 설정
        mysqlx::Schema schema = session->getSchema(dbname);

        // 인자로 받은 sql을 실행
        session->sql(sql).execute();

        // insert에 성공하였을 시 true로 변환 함
        Qresult.success = true;
    }
    catch (const mysqlx::Error& err)
    {
        // Error message를 담아서 리턴함
        std::string ErrorString = std::format(
        "DeleteQuery Error: ",
            err.what()
        );

        Qresult.errorMessage = ErrorString;
        std::cerr << ErrorString << std::endl;
    }

    return Qresult;
};


// mysql 연결 해제함
void Mysql::disconnect() const
{
    session->close();
};

