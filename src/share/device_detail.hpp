#pragma once

#include "boost_defs.hpp"

#include "iokit_utility.hpp"
#include "json_utility.hpp"
#include "types.hpp"
#include <boost/optional.hpp>
#include <pqrs/osx/iokit_types.hpp>

namespace krbn {
class device_detail final {
public:
  device_detail(pqrs::osx::iokit_registry_entry_id registry_entry_id,
                boost::optional<vendor_id> vendor_id,
                boost::optional<product_id> product_id,
                boost::optional<location_id> location_id,
                boost::optional<std::string> manufacturer,
                boost::optional<std::string> product,
                boost::optional<std::string> serial_number,
                boost::optional<std::string> transport,
                boost::optional<bool> is_keyboard,
                boost::optional<bool> is_pointing_device) : registry_entry_id_(registry_entry_id),
                                                            vendor_id_(vendor_id),
                                                            product_id_(product_id),
                                                            location_id_(location_id),
                                                            manufacturer_(manufacturer),
                                                            product_(product),
                                                            serial_number_(serial_number),
                                                            transport_(transport),
                                                            is_keyboard_(is_keyboard),
                                                            is_pointing_device_(is_pointing_device) {
  }

  device_detail(pqrs::osx::iokit_registry_entry_id registry_entry_id,
                IOHIDDeviceRef device) : device_detail(registry_entry_id,
                                                       iokit_utility::find_vendor_id(device),
                                                       iokit_utility::find_product_id(device),
                                                       iokit_utility::find_location_id(device),
                                                       iokit_utility::find_manufacturer(device),
                                                       iokit_utility::find_product(device),
                                                       iokit_utility::find_serial_number(device),
                                                       iokit_utility::find_transport(device),
                                                       iokit_utility::is_keyboard(device),
                                                       iokit_utility::is_pointing_device(device)) {
  }

  nlohmann::json to_json(void) const {
    nlohmann::json json;

    json["registry_entry_id"] = type_safe::get(registry_entry_id_);

    if (vendor_id_) {
      json["vendor_id"] = type_safe::get(*vendor_id_);
    }
    if (product_id_) {
      json["product_id"] = type_safe::get(*product_id_);
    }
    if (location_id_) {
      json["location_id"] = type_safe::get(*location_id_);
    }
    if (manufacturer_) {
      json["manufacturer"] = *manufacturer_;
    }
    if (product_) {
      json["product"] = *product_;
    }
    if (serial_number_) {
      json["serial_number"] = *serial_number_;
    }
    if (transport_) {
      json["transport"] = *transport_;
    }
    if (is_keyboard_) {
      json["is_keyboard"] = *is_keyboard_;
    }
    if (is_pointing_device_) {
      json["is_pointing_device"] = *is_pointing_device_;
    }

    return json;
  }

  boost::optional<vendor_id> get_vendor_id(void) const {
    return vendor_id_;
  }

  boost::optional<product_id> get_product_id(void) const {
    return product_id_;
  }

  boost::optional<location_id> get_location_id(void) const {
    return location_id_;
  }

  boost::optional<std::string> get_manufacturer(void) const {
    return manufacturer_;
  }

  boost::optional<std::string> get_product(void) const {
    return product_;
  }

  boost::optional<std::string> get_serial_number(void) const {
    return serial_number_;
  }

  boost::optional<std::string> get_transport(void) const {
    return transport_;
  }

  boost::optional<pqrs::osx::iokit_registry_entry_id> get_registry_entry_id(void) const {
    return registry_entry_id_;
  }

  boost::optional<bool> get_is_keyboard(void) const {
    return is_keyboard_;
  }

  boost::optional<bool> get_is_pointing_device(void) const {
    return is_pointing_device_;
  }

  bool compare(const device_detail& other) {
    // product
    {
      auto p1 = make_product_value();
      auto p2 = other.make_product_value();
      if (p1 != p2) {
        return p1 < p2;
      }
    }

    // manufacturer
    {
      auto m1 = make_manufacturer_value();
      auto m2 = other.make_manufacturer_value();
      if (m1 != m2) {
        return m1 < m2;
      }
    }

    // is_keyboard
    {
      auto k1 = make_is_keyboard_value();
      auto k2 = other.make_is_keyboard_value();
      if (k1 != k2) {
        return k1;
      }
    }

    // is_pointing_device
    {
      auto p1 = make_is_pointing_device_value();
      auto p2 = other.make_is_pointing_device_value();
      if (p1 != p2) {
        return p1;
      }
    }

    // registry_entry_id
    {
      auto r1 = registry_entry_id_;
      auto r2 = other.registry_entry_id_;
      if (r1 != r2) {
        return r1 < r2;
      }
    }

    return false;
  }

private:
  std::string make_manufacturer_value(void) const {
    if (manufacturer_) {
      return *manufacturer_;
    }
    return "";
  }

  std::string make_product_value(void) const {
    if (product_) {
      return *product_;
    }
    return "";
  }

  bool make_is_keyboard_value(void) const {
    if (is_keyboard_) {
      return *is_keyboard_;
    }
    return false;
  }

  bool make_is_pointing_device_value(void) const {
    if (is_pointing_device_) {
      return *is_pointing_device_;
    }
    return false;
  }

  pqrs::osx::iokit_registry_entry_id registry_entry_id_;
  boost::optional<vendor_id> vendor_id_;
  boost::optional<product_id> product_id_;
  boost::optional<location_id> location_id_;
  boost::optional<std::string> manufacturer_;
  boost::optional<std::string> product_;
  boost::optional<std::string> serial_number_;
  boost::optional<std::string> transport_;
  boost::optional<bool> is_keyboard_;
  boost::optional<bool> is_pointing_device_;
};

inline void to_json(nlohmann::json& json, const device_detail& device_detail) {
  json = device_detail.to_json();
}
} // namespace krbn
