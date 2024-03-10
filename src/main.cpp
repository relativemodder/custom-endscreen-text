#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EndLevelLayer.hpp>


std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


std::string getRandomTextString() {
	auto path = Mod::get()->getSettingValue<ghc::filesystem::path>("strings-file");
	auto result = geode::utils::file::readString(path);

	log::debug("Path: {}", path);

	if (!result) {
		auto error_ = std::string(result.error().c_str());
		FLAlertLayer::create(
			"Error!", 
			gd::string(std::string(std::string("<cr>Error: </c>") + error_).c_str()), 
			"OK"
		)->show();
		return error_;
	}

	auto content = result.unwrap();
	auto strings = split(content, "\n");

    int randomIndex = rand() % strings.size();
    std::string selectedElement = strings[randomIndex];

	return selectedElement;
}


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

		//auto value = Mod::get()->getSettingValue<std::string>("static-text");

		auto value = getRandomTextString();
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