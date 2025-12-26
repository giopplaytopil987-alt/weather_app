#pragma once

#include <string>
#include <stdint.h>
#include <ctime>
#include <httplib.h>
#include <nlohmann/json.hpp>

#define API_URL "https://api.openweathermap.org"
#define API_KEY "842f1185c8d8d9cfd7307fb68830a112"
#define DEFAULT_TIMEOUT 30

struct WeatherInfo  // Информация о полученной погоде
{
    std::string city_name{""};          // Название города - строка
    std::string weather{""};
    std::string weather_desc{""};       // Описание погоды - строка
    double temp{0.0};                   // Температура - Кельвин, Цельсий, Фаренгейт
    double feels_like{0.0};             // Восприятие погоды - Кельвин, Цельсий, Фаренгейт
    int32_t pressure{0};                // АД на уровне моря гПа - int32_t 
    unsigned humidity{0};               // Влажность - %
    double temp_min{0.0};               // Температура - Кельвин, Цельсий, Фаренгейт
    double temp_max{0.0};               // Температура - Кельвин, Цельсий, Фаренгейт
    int32_t sea_level{0};               // АД на уровне моря гПа - int32_t 
    int32_t grnd_level{0};              // АД на уровне земли гПа- int32_t
    unsigned visibility{0};             // Видимость - метры
    double wind_speed{0.0};             // Скорость ветра
    unsigned clouds_all{0};             // Облачность - %
    time_t sys_sunrise{0};              // time_t
    time_t sys_sunset{0};               // time_t
};
using wi = struct WeatherInfo;

class WeatherClient
{
    httplib::Client cli_{API_URL};
    std::string api_key_{API_KEY};
    std::string city_{""};
    std::string units_{""};
    wi data_{};
public:
    WeatherClient() = default;
    WeatherClient(int timeout);
    ~WeatherClient() = default;
    void set_city(std::string city);
    std::string get_city() const;
    void set_units(std::string units);
    std::string get_units() const;
    int send_request_weather();    // Принцип RESTAPI - Клиент умеет только запрашивать
    wi get_data() const;
};