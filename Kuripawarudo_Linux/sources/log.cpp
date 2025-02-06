#include "../headers/log.h"

void color_formatter(logging::record_view const& rec, logging::formatting_ostream& strm)
{
    auto severity = rec[logging::trivial::severity];
    if (severity)
    {
        // Set the color
        switch (severity.get())
        {
        case logging::trivial::severity_level::debug:   strm << "\033[36m"; break;
        case logging::trivial::severity_level::info:    strm << "\033[32m"; break;
        case logging::trivial::severity_level::warning: strm << "\033[33m"; break;
        case logging::trivial::severity_level::error:
        case logging::trivial::severity_level::fatal:   strm << "\033[31m"; break;
        default: break;
        }

        // Include the severity level in the log message
        strm << "[" << severity.get() << "] ";
    }

    // Format the message here...
    auto timestamp = boost::log::extract<boost::posix_time::ptime>("TimeStamp", rec);
    auto message = rec[boost::log::expressions::smessage];
    strm << "[" << timestamp << "]: " << message << reset;

    if (severity)
    {
        // Restore the default color
        strm << "\033[0m";
    }
}

void file_formatter(logging::record_view const& rec, logging::formatting_ostream& strm)
{
    auto severity = rec[logging::trivial::severity];
    if (severity)
    {
        // Include the severity level in the log message
        strm << "[" << severity.get() << "] ";
    }

    // Format the message here...
    auto timestamp = boost::log::extract<boost::posix_time::ptime>("TimeStamp", rec);
    auto message = rec[boost::log::expressions::smessage];
    strm << "[" << timestamp << "]: " << message;
}

void init_logging()
{
    if (!fs::exists("logs"))
        fs::create_directory("logs");

    // Log vers un fichier
    boost::log::add_file_log(
        boost::log::keywords::file_name = "logs/sample_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        boost::log::keywords::format = &file_formatter
    );

    // Log vers la console avec couleurs
    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::format = &color_formatter
    );

    logging::add_common_attributes();
}

void log_messages()
{
    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "This is a fatal severity message";
}

std::ostream& operator<< (std::ostream& strm, severity_level level)
{
    static const char* strings[] =
    {
        "trace",
        "debug",
        "info",
        "warning",
        "error",
        "fatal"
    };

    if (static_cast<std::size_t>(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast<int>(level);

    return strm;
}

std::ostream& red(std::ostream& s)
{
    return s << "\033[31m";
}

std::ostream& green(std::ostream& s)
{
    return s << "\033[32m";
}

std::ostream& yellow(std::ostream& s)
{
    return s << "\033[33m";
}

std::ostream& reset(std::ostream& s)
{
    return s << "\033[0m";
}