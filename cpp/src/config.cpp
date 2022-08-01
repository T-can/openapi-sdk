#include "config.hpp"
#include "callback.hpp"
#include "convert.hpp"
#include "longbridge.h"

namespace longbridge {

Config::Config()
{
  config_ = nullptr;
}

Config::Config(lb_config_t* config)
{
  config_ = config;
}

Config::Config(Config&& other)
{
  config_ = other.config_;
  other.config_ = nullptr;
}

Config::Config(const std::string& app_key,
               const std::string& app_secret,
               const std::string& access_token,
               const std::optional<std::string>& http_url,
               const std::optional<std::string>& quote_ws_url,
               const std::optional<std::string>& trade_ws_url,
               const std::optional<Language>& language)
{
  lb_language_t c_language;
  if (language) {
    c_language = convert::convert(*language);
  }

  config_ = lb_config_new(app_key.c_str(),
                          app_secret.c_str(),
                          access_token.c_str(),
                          http_url ? http_url->c_str() : nullptr,
                          http_url ? quote_ws_url->c_str() : nullptr,
                          http_url ? trade_ws_url->c_str() : nullptr,
                          language ? &c_language : nullptr);
}

Config::~Config()
{
  if (config_) {
    lb_config_free(config_);
  }
}

Config::operator const lb_config_t*() const
{
  return config_;
}

Status
Config::from_env(Config& config)
{
  lb_error_t* err = nullptr;
  lb_config_t* config_ptr = lb_config_from_env(&err);
  Status status(err);
  if (status.is_ok()) {
    config.config_ = config_ptr;
  }
  return status;
}

void
Config::refresh_access_token(int64_t expired_at,
                             AsyncCallback<void*, std::string> callback)
{
  lb_config_refresh_access_token(
    config_,
    expired_at,
    [](auto res) {
      auto callback_ptr =
        callback::get_async_callback<void*, std::string>(res->userdata);
      Status status(res->error);

      if (status) {
        std::string access_token = (const char*)res->data;

        (*callback_ptr)(AsyncResult<void*, std::string>(
          nullptr, std::move(status), &access_token));
      } else {
        (*callback_ptr)(
          AsyncResult<void*, std::string>(nullptr, std::move(status), nullptr));
      }
    },
    new AsyncCallback<void*, std::string>(callback));
}

} // namespace longbridge