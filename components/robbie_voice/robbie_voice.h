#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/microphone/microphone.h"
#include <string>

namespace esphome {
namespace robbie_voice {

class RobbieVoice : public Component {
 public:
  void setup() override;
  void loop() override;

  void set_microphone(microphone::Microphone *mic) { this->mic_ = mic; }
  void set_vps_host(const std::string &host) { this->vps_host_ = host; }
  void set_vps_port(uint16_t port) { this->vps_port_ = port; }
  void set_vps_path(const std::string &path) { this->vps_path_ = path; }

  void start();
  void stop();
  bool is_running() const { return this->running_; }

 protected:
  bool connect_to_vps_();
  void disconnect_();
  void send_audio_data_();

  microphone::Microphone *mic_{nullptr};
  std::string vps_host_;
  uint16_t vps_port_{8081};
  std::string vps_path_{"/voice"};
  
  int socket_fd_{-1};
  bool running_{false};
  uint32_t last_send_{0};
};

// Actions
template<typename... Ts> class StartListeningAction : public Action<Ts...> {
 public:
  explicit StartListeningAction(RobbieVoice *parent) : parent_(parent) {}
  void play(Ts... x) override { this->parent_->start(); }
 protected:
  RobbieVoice *parent_;
};

template<typename... Ts> class StopListeningAction : public Action<Ts...> {
 public:
  explicit StopListeningAction(RobbieVoice *parent) : parent_(parent) {}
  void play(Ts... x) override { this->parent_->stop(); }
 protected:
  RobbieVoice *parent_;
};

}  // namespace robbie_voice
}  // namespace esphome
