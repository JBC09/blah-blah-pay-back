//
// Created by chanbin on 25. 3. 4.
//

#include "./customJwt.h";


// 토큰 검증하는 함수임
bool payJwt::vailed(std::string userToken)
{
    try
    {
       auto decoded = jwt::decode(userToken);

        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{secret})
        .with_issuer("auth_service");

        verifier.verify(decoded);

        return true;
    }
    catch (const jwt::error::token_verification_exception& e)
    {
        std::cout << "토큰 검증 실패: " << e.what() << std::endl;
        return false;

    }
    catch (const std::exception& e)
    {
        std::cout << "에러 발생: " << e.what() << std::endl;
        return false;
    }
};


// 인자를 넣어서 토큰을 가져오는 함수임
std::string payJwt::getToken(std::string& type, std::string& userId, std::string& role)
{
    // 타입을 받아서 적용
    token = (jwt::create().set_type(type).set_algorithm("HS256")

    // 인증 서비스와 주제는 유저토큰으로 설정 발급일은 현재 날짜 및 시간으로
  .set_issuer("auth_service").set_subject("userToken").set_issued_at(std::chrono::system_clock::now())

  //  만료일은 현재 시간에서 1시간 후에 만료 됨
  .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{1})

  // user_id와 role를 토큰 값에 넣기
  .set_payload_claim("user_id", jwt::claim(std::string(userId)))
  .set_payload_claim("role", jwt::claim(std::string(role)))

  // 토큰 암호화하여 싸인
  .sign(jwt::algorithm::hs256(secret)));

    return token;
}


