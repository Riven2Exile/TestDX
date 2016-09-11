/*

���ݶԻ���, ���ɶ�Ӧ��xml�ļ�



�����Tab ���Ӧ�����ɶ��XML�ļ�


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
        //         // ����pGui 
        //         return true;
        //     }

        bool GenFormatFile(cGuiControl* pCtrl);

        /*bool ReadFromFormatFile(); ��xml�ļ������ɲ��� */

        CUIAtom* GetAtom(ControlType t);

		cGuiControl *GenFormFromFile();

    private:
        
		cGuiControl *CreateCtrl(ControlType ctrl_type, cGuiControl* pFather);
		cGuiControl *doGenFormFromFile(TiXmlElement* pEle, cGuiControl* &pCtrl);

		void set_normal_attr(TiXmlElement* pEle, cGuiControl* &pCtrl);

        std::map<ControlType, UIEditor::CUIAtom*> m_atomUI;

    };






}; //end namespace UIEditor



