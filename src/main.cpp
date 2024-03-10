#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EndLevelLayer.hpp>


class $modify(CustomEndLevelLayer, EndLevelLayer) {

	void customSetup() {
		EndLevelLayer::customSetup();

		if (Loader::get()->getLoadedMod("suntle.compactendscreen")) {
			FLAlertLayer::create(
				"Error!", 
				"<cr>Error!</c> Custom End Text <cy>is not compatible</c> with <cr>Compact Endscreen Mod!</c>", 
				"OK"
			)->show();
			return;
		}

		auto value = Mod::get()->getSettingValue<std::string>("static-text");
		auto text_scale = Mod::get()->getSettingValue<double>("static-text-scale");

		auto complete_message = static_cast<TextArea*>(getChildByIDRecursive("complete-message"));
		auto end_text = static_cast<CCLabelBMFont*>(getChildByIDRecursive("end-text"));

		if (complete_message != nullptr) {
			complete_message->setString(gd::string(value.c_str()));
			return;
		}

		if (end_text != nullptr) {
			end_text->setString(value.c_str(), true);
			end_text->setScale(text_scale);
			return;
		}
	}
};