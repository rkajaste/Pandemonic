#include <string>

#include "store/Store.hpp"
#include "engine/renderers/TextRenderer.hpp"
#include "engine/renderers/UserInterfaceRenderer.hpp"
#include "engine/renderers/DialogBoxRenderer.hpp"
#include "engine/common/Util.hpp"
#include "engine/common/types.hpp"

class DialogBox {
    public:
        DialogBox(std::string identifier);
        ~DialogBox();

        void draw();
    
    private:
        TextRenderer* textRenderer;
        DialogBoxRenderer* renderer;
        std::vector<Dialog> dialogLines;

        glm::vec2 dialogSize;
        glm::vec2 dialogPosition;

        glm::vec2 avatarSize;
        glm::vec2 avatarPosition;

        glm::vec2 namePosition;

        glm::vec2 dialogTextPosition;

        void debounceDialogText(std::string text);
        void drawName(std::string name);
};
