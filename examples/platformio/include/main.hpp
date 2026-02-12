#pragma once

#include <ESP323248S035.hpp>

// The ESP32-3248S035 library defines View as a pure virtual class, which acts
// as an interface between the library and application GUI code.
//
// We must define a concrete implementation of View to act as the root window
// of the target device's GUI. The content of View is application-defined.
//
// NOTE: Do NOT make any lvgl API calls from the View constructor. These must be
//       performed in the View::init() method.

// Forward declarations of button handlers (defined in main.cpp)
extern void reset_button_handler(lv_event_t *e);
extern void settings_button_handler(lv_event_t *e);
extern void stop_button_handler(lv_event_t *e);

class Main: public bsp::View {
private:
  // Individual button and label references with unique names
  lv_obj_t *buttonStart = nullptr;
  lv_obj_t *labelStart = nullptr;
  
  lv_obj_t *buttonStop = nullptr;
  lv_obj_t *labelStop = nullptr;
  
  lv_obj_t *buttonMenu = nullptr;
  lv_obj_t *labelMenu = nullptr;
  
  lv_obj_t *buttonSettings = nullptr;
  lv_obj_t *labelSettings = nullptr;
  
  lv_obj_t *buttonReset = nullptr;
  lv_obj_t *labelReset = nullptr;
  
  lv_obj_t *buttonHome = nullptr;
  lv_obj_t *labelHome = nullptr;
  
public:
  Main() = default;
  ~Main() = default;

  bool init(lv_obj_t *root) override {
    if (nullptr == root) {
      // Use the default screen if no root view provided.
      root = lv_scr_act();
    }
    
    // Create a flex container that takes up the entire screen with padding
    lv_obj_t *flex_container = lv_obj_create(root);
    lv_obj_set_size(flex_container, LV_PCT(100), LV_PCT(100));
    lv_obj_set_pos(flex_container, 0, 0);
    lv_obj_set_style_bg_color(flex_container, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(flex_container, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(flex_container, 0, 0);
    lv_obj_set_style_pad_all(flex_container, 20, 0);
    
    // Set flex flow to row wrap with equal spacing
    // This creates 2 columns with 3 rows, filling the screen
    lv_obj_set_flex_flow(flex_container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(flex_container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER);
    
    // Create all 6 buttons with sizes that fill the available space
    // Available space: 320px width - 40px padding = 280px
    // 2 columns: (280 - 10gap) / 2 = 135px per button
    // Available height: 480px - 40px padding - 20px gap = 420px
    // 3 rows: (420 - 20gap) / 3 = 133px per button
    
    // Button 1: Start
    buttonStart = lv_button_create(flex_container);
    lv_obj_set_size(buttonStart, 135, 133);
    lv_obj_set_style_bg_color(buttonStart, lv_color_hex(0x0066CC), 0);
    lv_obj_set_style_border_width(buttonStart, 2, 0);
    lv_obj_set_style_border_color(buttonStart, lv_color_hex(0x0099FF), 0);
    labelStart = lv_label_create(buttonStart);
    lv_label_set_text(labelStart, "Start");
    lv_obj_center(labelStart);
    lv_obj_set_style_text_font(labelStart, &lv_font_montserrat_14, 0);
    
    // Button 2: Stop
    buttonStop = lv_button_create(flex_container);
    lv_obj_set_size(buttonStop, 135, 133);
    lv_obj_set_style_bg_color(buttonStop, lv_color_hex(0x0066CC), 0);
    lv_obj_set_style_border_width(buttonStop, 2, 0);
    lv_obj_set_style_border_color(buttonStop, lv_color_hex(0x0099FF), 0);
    labelStop = lv_label_create(buttonStop);
    lv_label_set_text(labelStop, "Stop");
    lv_obj_center(labelStop);
    lv_obj_set_style_text_font(labelStop, &lv_font_montserrat_14, 0);
    lv_obj_add_event_cb(buttonStop, stop_button_handler, LV_EVENT_CLICKED, nullptr);
    
    // Button 3: Menu
    buttonMenu = lv_button_create(flex_container);
    lv_obj_set_size(buttonMenu, 135, 133);
    lv_obj_set_style_bg_color(buttonMenu, lv_color_hex(0x0066CC), 0);
    lv_obj_set_style_border_width(buttonMenu, 2, 0);
    lv_obj_set_style_border_color(buttonMenu, lv_color_hex(0x0099FF), 0);
    labelMenu = lv_label_create(buttonMenu);
    lv_label_set_text(labelMenu, "Menu");
    lv_obj_center(labelMenu);
    lv_obj_set_style_text_font(labelMenu, &lv_font_montserrat_14, 0);
    
    // Button 4: Settings
    buttonSettings = lv_button_create(flex_container);
    lv_obj_set_size(buttonSettings, 135, 133);
    lv_obj_set_style_bg_color(buttonSettings, lv_color_hex(0x0066CC), 0);
    lv_obj_set_style_border_width(buttonSettings, 2, 0);
    lv_obj_set_style_border_color(buttonSettings, lv_color_hex(0x0099FF), 0);
    labelSettings = lv_label_create(buttonSettings);
    lv_label_set_text(labelSettings, "Settings");
    lv_obj_center(labelSettings);
    lv_obj_set_style_text_font(labelSettings, &lv_font_montserrat_14, 0);
    lv_obj_add_event_cb(buttonSettings, settings_button_handler, LV_EVENT_CLICKED, nullptr);
    
    // Button 5: Reset
    buttonReset = lv_button_create(flex_container);
    lv_obj_set_size(buttonReset, 135, 133);
    lv_obj_set_style_bg_color(buttonReset, lv_color_hex(0x0066CC), 0);
    lv_obj_set_style_border_width(buttonReset, 2, 0);
    lv_obj_set_style_border_color(buttonReset, lv_color_hex(0x0099FF), 0);
    labelReset = lv_label_create(buttonReset);
    lv_label_set_text(labelReset, "Reset");
    lv_obj_center(labelReset);
    lv_obj_set_style_text_font(labelReset, &lv_font_montserrat_14, 0);
    lv_obj_add_event_cb(buttonReset, reset_button_handler, LV_EVENT_PRESSED, nullptr);
    lv_obj_add_event_cb(buttonReset, reset_button_handler, LV_EVENT_RELEASED, nullptr);
    
    // Button 6: Home
    buttonHome = lv_button_create(flex_container);
    lv_obj_set_size(buttonHome, 135, 133);
    lv_obj_set_style_bg_color(buttonHome, lv_color_hex(0x0066CC), 0);
    lv_obj_set_style_border_width(buttonHome, 2, 0);
    lv_obj_set_style_border_color(buttonHome, lv_color_hex(0x0099FF), 0);
    labelHome = lv_label_create(buttonHome);
    lv_label_set_text(labelHome, "Home");
    lv_obj_center(labelHome);
    lv_obj_set_style_text_font(labelHome, &lv_font_montserrat_14, 0);
    
    return true;
  }

  void update(msecu32_t const now) override {
    // Update any subviews here.
  }

  std::string title() override {
    return "Main";
  }
};

Main root;
//bsp::ESP323248S035C target(root); // C++17 can deduce template parameter.
bsp::ESP323248S035C<Main> target(root); // Pre-C++17 requires explicit type.
