/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2020, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
#ifndef __INCLUDED_INIFILE_H__
#define __INCLUDED_INIFILE_H__

#include <initializer_list>
#include <map>
#include <string>
#include <vector>

#include <filesystem>

namespace wwiv {
namespace core {

class IniFile final {
public:
  IniFile(std::filesystem::path filename, std::initializer_list<const char*> sections);
  IniFile(const std::filesystem::path& filename,
          std::initializer_list<const std::string> sections);
  // Constructor/Destructor
  ~IniFile();

  // Member functions
  void Close() noexcept;
  [[nodiscard]] bool IsOpen() const noexcept { return open_; }

  template <typename T>
  T value(const std::string& key, const T& default_value) const {
    return static_cast<T>(GetNumericValueT(key, default_value));
  }

  template <typename T>
  T value(const std::string& key) const {
    return static_cast<T>(GetNumericValueT(key, T()));
  }

  std::string full_pathname() const noexcept { return path_.string(); }
  std::filesystem::path path() const noexcept { return path_; }

private:
  // This class should not be assignable via '=' so remove the implicit operator=
  // and Copy constructor.
  IniFile(const IniFile& other) = delete;
  IniFile& operator=(const IniFile& other) = delete;
  const char* GetValue(const std::string& key, const char* default_value = nullptr) const;

  std::string GetStringValue(const std::string& key, const std::string& default_value) const;
  long GetNumericValueT(const std::string& key, long default_value = 0) const;
  bool GetBooleanValue(const std::string& key, bool default_value = false) const;

  const std::filesystem::path path_;
  bool open_{false};
  std::vector<std::string> sections_;
  std::map<std::string, std::string> data_;
};

template <>
std::string IniFile::value<std::string>(const std::string& key,
                                        const std::string& default_value) const;

template <>
std::string IniFile::value<std::string>(const std::string& key) const;

template <>
bool IniFile::value<bool>(const std::string& key, const bool& default_value) const;
template <>
bool IniFile::value<bool>(const std::string& key) const;


} // namespace core
} // namespace wwiv

#endif  // __INCLUDED_INIFILE_H__
