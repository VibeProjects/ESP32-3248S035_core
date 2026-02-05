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
class Main: public bsp::View {
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
    for (int i = 1; i <= 6; i++) {
      lv_obj_t *btn = lv_button_create(flex_container);
      lv_obj_set_size(btn, 135, 133);
      lv_obj_set_style_bg_color(btn, lv_color_hex(0x0066CC), 0);
      lv_obj_set_style_border_width(btn, 2, 0);
      lv_obj_set_style_border_color(btn, lv_color_hex(0x0099FF), 0);
      
      lv_obj_t *label = lv_label_create(btn);
      lv_label_set_text_fmt(label, "BTN %d", i);
      lv_obj_center(label);
      lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
    }
    
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
