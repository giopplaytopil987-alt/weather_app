#pragma once

#include <WeatherClient.h>
#include <memory>

enum Choice
{
    ENTER_DEFAULT = 0,
    ENTER_CITY = 1,
    ENTER_METRIC = 2
};

enum class TempMode
{
    STANDART,   // Кельвин
    METRIC,     // Цельсий
    IMPERIAL    // Фаренгейт
};

class AppMenu
{
    std::unique_ptr<WeatherClient> WeatherClient_;
    TempMode tempMode_ = TempMode::STANDART;
public:
    AppMenu();
    void user_choice();
    void show_weather();
};