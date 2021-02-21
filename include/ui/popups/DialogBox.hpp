#include <string>

#include "store/Store.hpp"
#include "engine/renderers/TextRenderer.hpp"
#include "engine/renderers/UserInterfaceRenderer.hpp"
#include "engine/common/Util.hpp"
#include "engine/common/types.hpp"

class DialogBox {
    public:
        DialogBox(std::string identifier);
        ~DialogBox();
        void draw(UserInterfaceRenderer* renderer);
    
    private:
        TextRenderer* textRenderer;
        std::vector<Dialog> dialogLines;

        void debounceText(std::string text);
};
