#pragma once

#include <ostream>
#include <memory>
#include <string>

#include <c10/macros/Export.h>
#include <c10/util/Deprecated.h>

namespace torch {
namespace lazy {

// Backend should extend it and define their own supported hardware types.
struct TORCH_API BackendDeviceType {
  int8_t type {0};

  virtual ~BackendDeviceType() = default;
  virtual std::string toString() const { return "Unknown"; }
};

class TORCH_API BackendDevice {
 public:
  BackendDevice();
  BackendDevice(std::shared_ptr<BackendDeviceType>&& type, int ordinal);

  int8_t type() const;
  int64_t ordinal() const { return ordinal_;  }

  bool operator==(const BackendDevice& other) const { return compare(other) == 0; }
  bool operator!=(const BackendDevice& other) const { return compare(other) != 0; }
  bool operator<(const BackendDevice& rhs) const { return compare(rhs) < 0; }

  std::string toString() const;

  // The string -> Device conversion should be handled by the backend interface.
  C10_DEPRECATED explicit BackendDevice(const std::string& device_spec);

 private:
  int compare(const BackendDevice& rhs) const;

  // Use shared_ptr instead of unique_ptr so that BackendDevice can be copied.
  std::shared_ptr<BackendDeviceType> type_;
  int64_t ordinal_ {0};
};

TORCH_API std::ostream& operator<<(std::ostream& os, const BackendDevice& device);

}  // namespace lazy
}  // namespace torch
