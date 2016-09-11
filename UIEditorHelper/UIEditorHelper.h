/*

根据对话框, 生成对应的xml文件



如果有Tab 项，则应该生成多个XML文件


*/
#include <map>

class cGuiControl;
class TiXmlElement;
enum ControlType;

namespace UIEditor
{

    class CUIAtom;
    

    class CUIEditorHelper
    {
    public:
        CUIEditorHelper();
        virtual ~CUIEditorHelper();


        //     typename <typename T, typename Ctrl>
        //     bool GenFormatFile(T file, Ctrl *pGui){
        //         
        //         // 遍历pGui 
        //         return true;
        //     }

        bool GenFormatFile(cGuiControl* pCtrl);

        /*bool ReadFromFormatFile(); 从xml文件中生成布局 */

        CUIAtom* GetAtom(ControlType t);

		cGuiControl *GenFormFromFile();

    private:
        
		cGuiControl *CreateCtrl(ControlType ctrl_type, cGuiControl* pFather);
		cGuiControl *doGenFormFromFile(TiXmlElement* pEle, cGuiControl* &pCtrl);

		void set_normal_attr(TiXmlElement* pEle, cGuiControl* &pCtrl);

        std::map<ControlType, UIEditor::CUIAtom*> m_atomUI;

    };






}; //end namespace UIEditor



