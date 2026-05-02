#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/PauseLayer.hpp> //refrence pauselayer and creatorlayer so the buttons can be placed correctly

class $modify(MyMenuLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) {
            return false;
        }

        log::debug("Hello from my CreatorLayer::init hook! This layer has {} children.", this->getChildrenCount());

        auto myButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("diffIcon_07_btn_001.png"),
            this,
            menu_selector(MyMenuLayer::onMyButton)
        );
        auto mySecondButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("diffIcon_auto_btn_001.png"),
            this,
            menu_selector(MyMenuLayer::onMySecondButton)
        );

        auto myThirdButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_rateDiffBtnMod_001.png"),
            this,
            menu_selector(MyMenuLayer::onMyThirdButton)
        );

        auto menu = this->getChildByID("bottom-right-menu");
        menu->addChild(myButton);
        myButton->setID("my-button"_spr);

        menu->addChild(mySecondButton);
        mySecondButton->setID("my-second-button"_spr);

        menu->addChild(myThirdButton);
        myThirdButton->setID("my-third-button"_spr); //I just kept the default names lmao

        menu->updateLayout();

        return true;
    }

    void onMyButton(CCObject*) {
        std::vector<std::string> messages = { //very simple list added
            "Beat Back On Track!",     "Beat Clubstep!",          "Beat Dash!",
            "Beat Fingerdash!",
            "Make.. an level?",
            "Beat XStep!",    "Beat an unrated level!",
            "Beat an challenge level!",
            "Beat Deadlocked!",
            "Beat Time Machine!",
            "Beat an easy list!",
            "Beat an insane list!",     "Beat an demon list!",
            "Beat Clutterfunk!",
            "Beat three demons!",
            "Beat an demon platformer level!",
            "Beat an trending level!",
            "Beat an most downloaded level!",
            "Earn 5 stars!",
            "Earn 50 diamonds!",
            "Do your daily level!",
            "Do your event level!",
            "Earn an demon key!",
            "Open five chests!",
            "Beat an level you've never played before!",
            "Beat the most easy level you know!",
            "Beat Hexagon Force!",
            "Beat an level from the recent tab!",
            "Beat any level!",
            "Get as far as you can in an extreme demon!",
            "Complete your ACTUAL quests!",
            "Touch grass! I'm sorry!",
            "Beat three insane levels!",
            "Beat an platformer level!",
            "Beat an insane level!",
            "Beat an EXTREME demon! (if you can)",
            "Beat an Easy Demon!",
            "Complete an auto level..",
            "Complete The Nightmare!",
        };

        int randomIndex = rand() % messages.size();
        std::string chosenMessage = messages[randomIndex];

        FLAlertLayer::create("QUEST", chosenMessage.c_str(), "OK")->show();
    }

    void onMySecondButton(CCObject*) {
        auto object = DialogObject::create("Potbor", "Featured Level you should play : Hyperdrive by Heptanone", 21, 1.f, true, {255, 255, 255});
        auto layer = DialogLayer::create(object, 2);
        layer->animateInRandomSide();
        layer->addToMainScene();
    }

    void onMyFifthButton(CCObject*) {
        auto object = DialogObject::create("Potbor", "Featured Level you should play : Hyperdrive by Heptanone", 21, 1.f, true, {255, 255, 255});
        auto layer = DialogLayer::create(object, 2);
        layer->animateInRandomSide();
        layer->addToMainScene();
    }

    void onMyThirdButton(CCObject*) {
        auto array = CCArray::create(); //I'll prob change this in the future

        auto object1 = DialogObject::create("The Mechanic", "why have you clicked the forbidden button", 46, 1.f, true, {255, 255, 255});
        auto object2 = DialogObject::create("The Mechanic", "whenever you hit that button he wakes up", 45, 1.f, true, {255, 255, 255});
        auto object3 = DialogObject::create("WHO IS HE?", "...", 4, 1.f, true, {255, 255, 255});
        auto object4 = DialogObject::create("WHO IS HE?", "AHHHHHHHHHHHHHHHHHHHHHHHHHHH", 18, 1.f, true, {255, 255, 255});
        auto object5 = DialogObject::create("Shopkeeper", "hey next time don't even think about pressing that button", 31, 1.f, true, {255, 255, 255});
        auto object6 = DialogObject::create("The Mechanic", "yes please I'm too young to die", 39, 1.f, true, {255, 255, 255});
        auto object7 = DialogObject::create("The Mechanic", "Also I hear something strange..", 50, 1.f, true, {255, 255, 255});
        auto object8 = DialogObject::create("...", "yo what up", 52, 1.f, true, {255, 255, 255});
        array->addObject(object1);
        array->addObject(object2);
        array->addObject(object3);
        array->addObject(object4);
        array->addObject(object5);
        array->addObject(object6);
        array->addObject(object7);
        array->addObject(object8);
        auto layer = DialogLayer::createWithObjects(array, 2);
        layer->animateInRandomSide();
        layer->addToMainScene();
    }
};

class $modify(MyPauseLayer, PauseLayer) {
    struct Fields {
        float m_rotation = 0.f;
        int m_posStep = 0;
    };

    void customSetup() {
        PauseLayer::customSetup();

        auto myPauseButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("edit_enableRotateBtn_001.png"),
            this,
            menu_selector(MyPauseLayer::onTiltToggle)
        );

        auto myScaleButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("edit_eMoveComBtn_001.png"),
            this,
            menu_selector(MyPauseLayer::onPositionToggle)
        );

        auto menu = this->getChildByID("right-button-menu");
        if (menu) {
            menu->addChild(myPauseButton);
            myPauseButton->setID("my-pause-button"_spr);

            menu->addChild(myScaleButton);
            myScaleButton->setID("my-scale-button"_spr);

            menu->updateLayout();
        }
    }

    void onTiltToggle(CCObject*) {
        auto pl = PlayLayer::get();
        if (!pl) return;
        m_fields->m_rotation += 25.f;

        if (m_fields->m_rotation > 175.f) {
            m_fields->m_rotation = 0.f;
        }

        pl->setRotationY(m_fields->m_rotation);
    }

    void onPositionToggle(CCObject*) {
        auto pl = PlayLayer::get();
        if (!pl) return;

        // I made it so it goes up to 170 for the position
        static const float xPositions[] = { 0.f, 120.f, 140.f, 150.f, 170.f };

        m_fields->m_posStep++;

        if (m_fields->m_posStep >= 5) {
            m_fields->m_posStep = 0;
        }

        float newX = xPositions[m_fields->m_posStep];
        auto currentPos = pl->getPosition();
        pl->setPosition({ newX, currentPos.y });
    }
};