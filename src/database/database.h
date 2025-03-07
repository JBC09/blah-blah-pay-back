//
// Created by chanbin on 25. 3. 4.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>

#include "../auth/customJwt.h"


// 쿼리 진행 후 결과
struct QueryResult
{
    // 결과 행을 담는 vector
    std::vector<std::map<std::string, std::string>> rows;

    // 해결된 코드를 반환
    size_t rowCount() const
    {
        return rows.size();
    }

    bool success = false;

    std::string errorMessage;
};

class Database {

private:
    bool isConnect; // DB connect check

    std::string host; // ex) localhost
    std::string user; // ex) root
    std::string password; // ex) 1234
    std::string dbname; // ex) cummunity

    int port; // ex) 33060

    payJwt jwtHandler; // CustomJwt

public:

    // 데이터 베이스 연결하기
    virtual void connect(std::string& host, std::string& dbname, std::string& user, std::string& password, int port) const = 0;

    // 데이터 베이스 쿼리 날리기 기본적인 CRUD
    virtual QueryResult insertQuery(std::string& sql) const = 0;

    virtual QueryResult selectQuery(std::string& sql) const = 0;

    virtual QueryResult updateQuery(std::string& sql) const = 0;

    virtual QueryResult deleteQuery(std::string& sql) const = 0;


    // 데이터베이스 연결 해제
    virtual void disconnect() const = 0;

    // 가상 생성자 및 소멸자
    Database() = default;
    ~Database() = default;
};





#endif //DATABASE_H
