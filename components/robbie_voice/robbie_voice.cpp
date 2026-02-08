#include "robbie_voice.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

namespace esphome {
namespace robbie_voice {

static const char *TAG = "robbie_voice";

void RobbieVoice::setup() {
  ESP_LOGI(TAG, "Robbie Voice component initialized");
  ESP_LOGI(TAG, "VPS: %s:%d%s", this->vps_host_.c_str(), this->vps_port_, this->vps_path_.c_str());
}

void RobbieVoice::loop() {
  if (!this->running_) {
    return;
  }

  // Send audio data periodically
  this->send_audio_data_();
}

void RobbieVoice::start() {
  if (this->running_) {
    ESP_LOGW(TAG, "Already running");
    return;
  }

  ESP_LOGI(TAG, "Starting voice capture...");
  
  if (!this->connect_to_vps_()) {
    ESP_LOGE(TAG, "Failed to connect to VPS");
    return;
  }

  // Start the microphone
  if (this->mic_ != nullptr) {
    this->mic_->start();
  }
  
  this->running_ = true;
  ESP_LOGI(TAG, "Voice capture started");
}

void RobbieVoice::stop() {
  if (!this->running_) {
    return;
  }

  ESP_LOGI(TAG, "Stopping voice capture...");
  
  // Stop the microphone
  if (this->mic_ != nullptr) {
    this->mic_->stop();
  }
  
  this->disconnect_();
  this->running_ = false;
  ESP_LOGI(TAG, "Voice capture stopped");
}

bool RobbieVoice::connect_to_vps_() {
  ESP_LOGI(TAG, "Connecting to VPS %s:%d...", this->vps_host_.c_str(), this->vps_port_);

  // Resolve hostname
  struct hostent *server = gethostbyname(this->vps_host_.c_str());
  if (server == nullptr) {
    ESP_LOGE(TAG, "Failed to resolve hostname: %s", this->vps_host_.c_str());
    return false;
  }

  // Create socket
  this->socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (this->socket_fd_ < 0) {
    ESP_LOGE(TAG, "Failed to create socket: %d", errno);
    return false;
  }

  // Set up server address
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  server_addr.sin_port = htons(this->vps_port_);

  // Connect
  int err = ::connect(this->socket_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (err < 0) {
    ESP_LOGE(TAG, "Failed to connect: %d", errno);
    close(this->socket_fd_);
    this->socket_fd_ = -1;
    return false;
  }

  // Set non-blocking
  int flags = fcntl(this->socket_fd_, F_GETFL, 0);
  fcntl(this->socket_fd_, F_SETFL, flags | O_NONBLOCK);

  ESP_LOGI(TAG, "Connected to VPS successfully");
  return true;
}

void RobbieVoice::disconnect_() {
  if (this->socket_fd_ >= 0) {
    close(this->socket_fd_);
    this->socket_fd_ = -1;
  }
  ESP_LOGI(TAG, "Disconnected");
}

void RobbieVoice::send_audio_data_() {
  if (this->socket_fd_ < 0 || this->mic_ == nullptr) {
    return;
  }

  // Read audio data from microphone
  // The microphone component provides audio samples
  // For now, just log that we would send data
  uint32_t now = millis();
  if (now - this->last_send_ > 1000) {
    ESP_LOGD(TAG, "Would send audio data...");
    this->last_send_ = now;
  }
}

}  // namespace robbie_voice
}  // namespace esphome
