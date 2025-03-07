//
// Created by chanbin on 25. 3. 4.
//

#ifndef JWT_H
#define JWT_H


#include <jwt-cpp/jwt.h>

class payJwt
{

private:
    std::string token; // 주고 받는 토큰임
    std::string secret; // 시크릿 키

public:

    payJwt() : secret("1valskdfhalkdjhfaisdyfuia6df7a86sdf7adfjkadhfa8dfya87"){};
    ~payJwt() = default;

    std::string getToken(std::string& type, std::string& userId, std::string& role);

    bool vailed(std::string userToken);
};




#endif //JWT_H
