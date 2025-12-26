#include <AppMenu.h>

AppMenu::AppMenu() : WeatherClient_{std::make_unique<WeatherClient>(DEFAULT_TIMEOUT)}
{
    WeatherClient_->set_city("Moscow");
    WeatherClient_->set_units("standart");
    show_weather(); 
}

void AppMenu::user_choice()
{
    std::cout << "Нажмите 0 -> Москва, цельсия\n";
    std::cout << "Нажмите 1 -> для ввода города\n";
    std::cout << "Нажмите 2 -> для ввода единиц\n";
    std::cout << "Выход -> Ctrl + C\n";
    int ch = 0; std::cin >> ch;
    switch(ch)
    {
        case Choice::ENTER_DEFAULT: {
            WeatherClient_->set_city("Moscow");
            WeatherClient_->set_units("standart");
            tempMode_ = TempMode::STANDART;
            break;
        }
        case Choice::ENTER_CITY: {
            std::cout << "Введите город\n";
            std::string city{""};
            std::cin >> city;
            WeatherClient_->set_city(city);
            // TODO: добавить проверку города и перевод через GOOGLE TRANSLATE API или от YANDEX
            break;
        }
        case Choice::ENTER_METRIC: {
            std::cout << "Введите единицы измерения для температуры:standart/metric/imperial\n";
            std::string units{""};
            std::cin >> units;
            WeatherClient_->set_units(units);
            if (units == "standart")
                tempMode_ = TempMode::STANDART;
            else if (units == "metric")
                tempMode_ = TempMode::METRIC;
            else if (units == "imperial")
                tempMode_ = TempMode::IMPERIAL;
            else {
                std::cout << "Invalid. use default\n";
                WeatherClient_->set_units("standart");
            }
            break;
        }
        default: {
            WeatherClient_->set_city("Moscow");
            WeatherClient_->set_units("standart");
            tempMode_ = TempMode::STANDART;
            std::cout << "Invalid. use default\n";
            break;
        }
    };
    show_weather();
}

void AppMenu::show_weather()
{
    // TODO: Сделать красивое отображение значений
    system("clear");
    if (WeatherClient_->send_request_weather() != -1) {
        std::cout << "-----------------------------------\n";
        std::cout << "Город: " << WeatherClient_->get_data().city_name << "\n";
        std::cout << "Погода: " << WeatherClient_->get_data().weather << "\n";
        std::cout << "Описание погоды: " << WeatherClient_->get_data().weather_desc << "\n";
        auto showTMP = [&](bool flagWind) {
            switch(tempMode_)
            {
                case TempMode::STANDART: {
                    (!flagWind) ? std::cout << " Кельвин\n" : std::cout << " м/c\n";
                    break;
                }
                case TempMode::METRIC: {
                    (!flagWind) ? std::cout << " Цельсий\n" : std::cout << " м/c\n";
                    break;
                }
                case TempMode::IMPERIAL: {
                    (!flagWind) ? std::cout << " Фаренгейт\n" : std::cout << " мили/час\n";
                    break;
                }
            }
        };
        std::cout << "Температура: " << WeatherClient_->get_data().temp; 
        showTMP(false);
        std::cout << "Восприятие погоды: " << WeatherClient_->get_data().feels_like << "\n";
        std::cout << "Атмосферное давление: " << WeatherClient_->get_data().pressure << " гПа\n";
        std::cout << "Влажность: " << WeatherClient_->get_data().humidity << "%\n";
        std::cout << "Минимальная температура: " << WeatherClient_->get_data().temp_min;
        showTMP(false);
        std::cout << "Максимальная температура: " << WeatherClient_->get_data().temp_max;
        showTMP(false);
        std::cout << "Атмосферное давление над уровнем моря: " << WeatherClient_->get_data().sea_level << " гПа\n";
        std::cout << "Атмосферное давление над уровнем земли: " << WeatherClient_->get_data().grnd_level << " гПа\n";
        std::cout << "Видимость: " << WeatherClient_->get_data().visibility << " метров\n";
        std::cout << "Скорость ветра: " << WeatherClient_->get_data().wind_speed;
        showTMP(true);
        std::cout << "Облачность: " << WeatherClient_->get_data().clouds_all << "%\n";
        time_t t1 = WeatherClient_->get_data().sys_sunrise;
        time_t t2 = WeatherClient_->get_data().sys_sunset;
        struct tm* timeinfo_utc1 = gmtime(&t1);
        struct tm* timeinfo_utc2 = gmtime(&t2);
        std::cout << "UTC время восхода солнца: " << timeinfo_utc1->tm_mday << "." << timeinfo_utc1->tm_mon + 1 << "." << timeinfo_utc1->tm_year + 1900 << " "
                << timeinfo_utc1->tm_hour << ":" << timeinfo_utc1->tm_min << ":" << timeinfo_utc1->tm_sec << std::endl;
        std::cout << "UTC время заката солнца: " << timeinfo_utc2->tm_mday << "." << timeinfo_utc2->tm_mon + 1 << "." << timeinfo_utc2->tm_year + 1900 << " "
                << timeinfo_utc2->tm_hour << ":" << timeinfo_utc2->tm_min << ":" << timeinfo_utc2->tm_sec << std::endl;
        std::cout << "-----------------------------------\n";
    }
    user_choice();
}