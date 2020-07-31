


namespace aspen
{

class BaseConfigItem
{
public:
    virtual ~BaseConfigItem() {}
};

template <class T>
class ConfigItem : public BaseConfigItem
{
	
public:

    //takes in a string value and sets mValue to its T type
    void strToType(std::string value){
        mValue = boost::lexical_cast<T>(value);
    }

    //Takes in a string value and returns its boolean type
    bool strToBool(std::string value){
        return boost::lexical_cast<bool>(value);
    }

    //takes in a boolean value and returns its string type
    std::string boolToStr(bool value){
        return boost::lexical_cast<std::string>(value);
    }

    //returns the string format of the config item's value
    std::string text(){
        std::ostringstream ss;
        ss << mValue;
        return ss.str();
    }

    T mValue;

};

}
