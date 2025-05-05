/**
    @title     MoonLight
    @file      Layouts.h
    @repo      https://github.com/MoonModules/MoonLight, submit changes to this file as PRs
    @Authors   https://github.com/MoonModules/MoonLight/commits/main
    @Doc       https://moonmodules.org/MoonLight/general/utilities/
    @Copyright © 2025 Github MoonLight Commit Authors
    @license   GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
    @license   For non GPL-v3 usage, commercial licenses must be purchased. Contact moonmodules@icloud.com
**/

#if FT_MOONLIGHT

class LayoutNode: public Node {
public:

  void setup() override {
    layerV->layerP->lights.header.channelsPerLight = sizeof(CRGB); //default

    //redundant?
    for (layerV->layerP->pass = 1; layerV->layerP->pass <= 2; layerV->layerP->pass++)
      map(); //calls also addLayout
  }

  //calls addLayout functions, non virtual, only addLayout can be redefined in derived class
  void map() {

    if (on) {
      layerV->layerP->addLayoutPre();
      addLayout();
      layerV->layerP->addLayoutPost();
    } else {
      layerV->resetMapping();
    }
  }

  virtual void addLayout() {
  }

  virtual void destructor() {
    layerV->resetMapping();
  }

};

class PanelLayout: public LayoutNode {
  const char * name() override {return "Panel🚥";}

  uint8_t width = 16;
  uint8_t height = 16;
  bool snake = true;

  void getControls(JsonArray controls) override {
    hasLayout = true;
    JsonObject control;
    control = controls.add<JsonObject>(); control["name"] = "width"; control["type"] = "range"; control["default"] = 16; control["max"] = 32; control["value"] = width;
    control = controls.add<JsonObject>(); control["name"] = "height"; control["type"] = "range"; control["default"] = 16; control["max"] = 32; control["value"] = height;
    control = controls.add<JsonObject>(); control["name"] = "snake"; control["type"] = "checkbox"; control["default"] = true; control["value"] = snake;
  }
  
  void setControl(JsonObject control) override {
    ESP_LOGD(TAG, "%s = %s", control["name"].as<String>().c_str(), control["value"].as<String>().c_str());
    if (control["name"] == "width") width = control["value"];
    if (control["name"] == "height") height = control["value"];
    if (control["name"] == "snake") snake = control["value"];
    //if changed run map
    setup();
  }

  void addLayout() override {
    layerV->layerP->addPin(2); //not working yet

    for (int x = 0; x<width; x++) {
      for (int y = 0; y<height; y++) {
        layerV->layerP->addLight({x, (x%2 || !snake)?y:height-1-y, 0});
      }
    }
  }

};

class DMXLayout: public LayoutNode {

  uint8_t width = 4; //default 4 moving heads
  uint8_t type = ct_LedsRGBW; //default 4 moving heads

  void getControls(JsonArray controls) override {
    hasLayout = true;
    JsonObject control;
    JsonArray values;
    control = controls.add<JsonObject>(); control["name"] = "width"; control["type"] = "range"; control["default"] = 4; control["max"] = 32; control["value"] = width;
    control = controls.add<JsonObject>(); control["name"] = "type"; control["type"] = "select"; control["default"] = "CRGBW"; values = control["values"].to<JsonArray>();
    values.add("CRGB");
    values.add("CRGBW");
    values.add("CrazyCurtain");
    values.add("Movinghead");
    switch (type) {
      case ct_LedsRGBW: control["value"] = "CRGBW"; break;
      case ct_CrazyCurtain: control["value"] = "CrazyCurtain"; break;
      case ct_MovingHead: control["value"] = "Movinghead"; break;
      default: control["value"] = "CRGB"; break;
    };
}
  
  void setControl(JsonObject control) override {
    ESP_LOGD(TAG, "%s = %s", control["name"].as<String>().c_str(), control["value"].as<String>().c_str());
    if (control["name"] == "width") width = control["value"];
    if (control["name"] == "type") {
        if ( control["value"] == "CRGBW") type = ct_LedsRGBW;
        else if ( control["value"] == "CrazyCurtain") type = ct_CrazyCurtain;
        else if ( control["value"] == "Movinghead") type = ct_MovingHead;
        else type = ct_Leds;
    }
    //if changed run map
    setup();
  }

  void setup() override {
    LayoutNode::setup();
    switch (type) {
      case ct_LedsRGBW: layerV->layerP->lights.header.channelsPerLight = sizeof(CRGBW); break;
      case ct_CrazyCurtain: layerV->layerP->lights.header.channelsPerLight = sizeof(CrazyCurtain); break;
      case ct_MovingHead: layerV->layerP->lights.header.channelsPerLight = sizeof(MovingHead); break;
      default: layerV->layerP->lights.header.channelsPerLight = sizeof(CRGB); break;
    };
    
  }

  void addLayout() override {
    for (int x = 0; x<width; x++) {
      layerV->layerP->addLight({x, 0, 0});
    }
  }

};

#endif //FT_MOONLIGHT