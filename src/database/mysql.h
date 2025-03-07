//
// Created by chanbin on 25. 3. 4.
//

#ifndef MYSQL_H
#define MYSQL_H

#include "./database.h"
#include <mysqlx/xdevapi.h>


// 추상 클래스인 Database를 Mysql이 상속받음
class Mysql : public Database {

public:
    // 기본 생성자 소멸자
    Mysql() = default;
    ~Mysql() = default;

private:

    bool isConnect; // DB connect check

    std::string host; // ex) localhost
    std::string user; // ex) root
    std::string password; // ex) 1234
    std::string dbname; // ex) cummunity


    int port; // ex) 33060

    payJwt jwtHandler; // CustomJwt

    std::unique_ptr<mysqlx::Session> session;


public:
    // 데이터 베이스 연결하기
    void connect(std::string& host, std::string& dbname, std::string& user, std::string& password, int port);

    // 데이터 베이스 쿼리 날리기 기본적인 CRUD
    QueryResult insertQuery(std::string& sql) const override;

    QueryResult selectQuery(std::string& sql) const override;

    QueryResult updateQuery(std::string& sql) const override;

    QueryResult deleteQuery(std::string& sql) const override;

    // 데이터베이스 연결 해제
    void disconnect() const override;
};



#endif //MYSQL_H
