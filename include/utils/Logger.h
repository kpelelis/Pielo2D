#pragma once


#define TAG(X) '[' << X << "] "

#define RED "[31m"
#define GREEN "[32m"
#define YELLOW "[33m"
#define BLUE "[34m"
#define MAGENTA "[45m"

#define COLORED(MSG, COLOR) '\033' << COLOR << MSG << "\033[0m"

enum Level {
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    CRITICAL = 5
};

class Logger {
public:    
    
    template<typename ...Args>
    void log(const Level msg_level, const std::string& from, Args&& ...args) {
        if(msg_level < min_level) return;
        std::ostringstream stream;
        using List = int[];
        (void)List{0, ( (void)(stream << args), 0 ) ... };
        std::cout << TAG(timestamp()) << TAG(level_string(msg_level)) << TAG(from) << stream.str() << std::endl;
    }

    static Logger& get_instance() {
        static Logger instance;
        return instance;
    }

    static void set_min_level(const Level lvl) {
        get_instance().min_level = lvl;
    }

    Logger(const Logger&) = delete;             
    Logger& operator=(const Logger&) = delete;

private:

    Level min_level = Level::DEBUG;

    inline std::string const& to_string(std::string const& s) { return s; }
    const std::string level_string(const Level lvl) {
        std::ostringstream ss;
        switch(lvl) {
        case Level::DEBUG:
            ss << COLORED("DEBUG", BLUE);
            break; 
        case Level::INFO:
            ss << COLORED("INFO", GREEN);
            break; 
        case Level::WARN:
            ss << COLORED("WARNING", YELLOW);
            break; 
        case Level::ERROR:
            ss << COLORED("ERROR", RED);
            break; 
        case Level::CRITICAL:
            ss << COLORED("CRITICAL", MAGENTA);
            break; 
        }
        return ss.str();
    }

    const std::string timestamp() {
        time_t now = time(0);           
        tm *gmtm = gmtime(&now);
        char * dt = asctime(gmtm);
        int l = std::strlen(dt);
        dt[l - 1] = '\0';
        return std::string(dt);
    }

    Logger() {};
};