// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

//
// The ABICxxModule implements the CxxModule interface and wraps up the ABI-safe
// NativeModule.
//

#pragma once

#include "DynamicReader.h"
#include "DynamicWriter.h"
#include "ReactHost/React.h"
#include "cxxreact/CxxModule.h"
#include "winrt/Microsoft.ReactNative.h"

namespace winrt::Microsoft::ReactNative {

struct ABICxxModuleEventHandlerSetter {
  std::string Name;
  ReactEventHandlerSetter EventHandlerSetter;
};

struct ABICxxModule : facebook::xplat::module::CxxModule {
  ABICxxModule(
      winrt::Windows::Foundation::IInspectable &nativeModule,
      std::string &&name,
      std::string &&eventEmitterName,
      std::vector<facebook::xplat::module::CxxModule::Method> &&methods,
      std::vector<ConstantProvider> constants,
      std::vector<ABICxxModuleEventHandlerSetter> &&eventHandlerSetters,
      Mso::CntPtr<Mso::React::IReactContext> &&reactContext) noexcept;

 public: // CxxModule implementation
  std::string getName() override;
  std::map<std::string, folly::dynamic> getConstants() override;
  std::vector<facebook::xplat::module::CxxModule::Method> getMethods() override;

 private:
  void InitEvents(std::vector<ABICxxModuleEventHandlerSetter> const &eventHandlerSetters) noexcept;

 private:
  winrt::Windows::Foundation::IInspectable m_nativeModule;
  std::string m_name;
  std::string m_eventEmitterName;
  std::vector<facebook::xplat::module::CxxModule::Method> m_methods;
  std::vector<ConstantProvider> m_constants;
  Mso::CntPtr<Mso::React::IReactContext> m_reactContext;
};

} // namespace winrt::Microsoft::ReactNative
