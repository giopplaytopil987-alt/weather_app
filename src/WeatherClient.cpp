#include <WeatherClient.h>

WeatherClient::WeatherClient(int timeout)
{
    cli_.set_connection_timeout(timeout);
    cli_.set_read_timeout(timeout);
}

int WeatherClient::send_request_weather()
{
    std::string endpoint = "/data/2.5/weather?q=" + city_ + 
                            "&appid=" + api_key_ + 
                            "&units=" + units_ + 
                            "&lang=ru";
    auto res = cli_.Get(endpoint.c_str());
    if (!res) {
        std::cerr << "Ошибка запроса!" << std::endl;
        return -1;
    }
    std::cout << "Код ответа: " << res->status << std::endl;
    if (res->status == 200) {
        auto json = nlohmann::json::parse(res->body);
        data_.city_name = json["name"];
        data_.weather = json["weather"][0]["main"];
        data_.weather_desc = json["weather"][0]["description"];
        data_.temp = json["main"]["temp"];
        data_.feels_like = json["main"]["feels_like"];
        data_.pressure = json["main"]["pressure"];
        data_.humidity = json["main"]["humidity"];
        data_.temp_min = json["main"]["temp_min"];
        data_.temp_max = json["main"]["temp_max"];
        data_.sea_level = json["main"]["sea_level"];
        data_.grnd_level = json["main"]["grnd_level"];
        data_.visibility = json["visibility"];
        data_.wind_speed = json["wind"]["speed"];
        data_.clouds_all = json["clouds"]["all"];
        data_.sys_sunrise = json["sys"]["sunrise"];
        data_.sys_sunset = json["sys"]["sunset"];
    } else {
        std::cerr << "Ошибка(res->status!=200): " << res->body << std::endl;
        return -1;
    }
    return 1;
}

void WeatherClient::set_city(std::string city)
{
    this->city_ = city;
}

std::string WeatherClient::get_city() const
{
    return this->city_;
}

void WeatherClient::set_units(std::string units)
{
    this->units_ = units;
}

std::string WeatherClient::get_units() const
{
    return this->units_;
}

wi WeatherClient::get_data() const
{
    return this->data_;
}