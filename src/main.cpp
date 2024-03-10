#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EndLevelLayer.hpp>


class CallbackActions : public CCObject {
public:

	void showDelayedAlert() {
		FLAlertLayer::create(
			"Ooops!", 
			"Seems like you <cr>have no NodeIDs installed.</c> Consider installing it via <cy>Geode Mod Index.</c>", 
			"OK"
		)->show();
	}
};


class $modify(CustomEndLevelLayer, EndLevelLayer) {

	void customSetup() {
		EndLevelLayer::customSetup();
		auto value = Mod::get()->getSettingValue<std::string>("static-text");
		auto text_scale = Mod::get()->getSettingValue<double>("static-text-scale");

		TextArea* complete_message = static_cast<TextArea*>(getChildByIDRecursive("complete-message"));
		CCLabelBMFont* end_text = static_cast<CCLabelBMFont*>(getChildByIDRecursive("end-text"));

		if (complete_message != nullptr) {
			complete_message->setString(gd::string(value.c_str()));
			return;
		}

		if (end_text != nullptr) {
			end_text->setString(value.c_str(), true);
			end_text->setScale(text_scale);
			return;
		}


		auto action = CCCallFunc::create(this, callfunc_selector(CallbackActions::showDelayedAlert));
		CCArray* actions_array = CCArray::create();

		actions_array->addObject(CCDelayTime::create(0.5f));
		actions_array->addObject(action);

		// runAction(
		// 	CCSequence::create(actions_array)
		// );
	}
};