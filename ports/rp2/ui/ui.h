#pragma once

#include <cstdint>
//#include <iostream>
#include <boost/pfr.hpp>
#include <TFT_eSPI.h>


using namespace std;

struct Rect {
    int x;
    int y;
    int w;
    int h;
};

template<typename State>
class Widget {
public:
    State state;

    // widget config
    Rect viewport = {};

    explicit Widget(TFT_eSPI &tft, State initState) :
            state{initState}, tft{tft}, prevState{initState} {};


    bool isRedrawNeeded() {
        return !drawn || boost::pfr::ne_fields(prevState, state);
    }

    void draw(uint32_t millis) {
        //cout << "Redrawing " << typeid(*this).name() << endl;

        prevState = state;
        drawn = true;
        tft.setViewport(viewport.x, viewport.y, viewport.w, viewport.h);
        drawImpl(millis);
    }

    void drawIfNeeded(uint32_t millis) {
        if (isRedrawNeeded()) draw(millis);
    }

protected:
    TFT_eSPI &tft;

    void scheduleRedraw() {
        drawn = false;
    }

private:
    State prevState;
    bool drawn = false;

    virtual void drawImpl(uint32_t millis) = 0;
};

class View {
public:
    explicit View(TFT_eSPI &tft) : tft{tft} {};

    virtual void firstRender() = 0;
    virtual void render(uint32_t millis) = 0;

protected:
    TFT_eSPI &tft;
};