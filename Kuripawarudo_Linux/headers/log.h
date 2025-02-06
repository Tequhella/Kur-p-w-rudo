#ifndef LOG_H
#define LOG_H

#include "type.h"

#include <filesystem>
#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace fs = std::filesystem;
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

enum severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

/**
 * @brief Fonction color_formatter, permet de formatter les messages de log.
 * 
 * @param rec
 * @param strm 
 */
void color_formatter(logging::record_view const& rec, logging::formatting_ostream& strm);

/**
 * @brief Fonction file_formatter, permet de formatter les messages de log.
 * 
 * @param rec
 * @param strm 
 */
void file_formatter(logging::record_view const& rec, logging::formatting_ostream& strm);

/**
 * @brief Fonction init_logging, permet d'initialiser le logging.
 */
void init_logging();

/**
 * @brief Fonction log_messages, permet de logger des messages.
 */
void log_messages();

/**
 * @brief Opérateur <<, permet d'afficher le niveau de sévérité.
 * 
 * @param strm 
 * @param level 
 * @return std::ostream& 
 */
std::ostream& operator<< (std::ostream& strm, severity_level level);

/**
 * @brief BOOST_LOG_ATTRIBUTE_KEYWORD, permet de définir un attribut.
 */
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)

/**
 * @brief Fonction red, permet d'afficher du texte en rouge.
 * 
 * @param s 
 * @return std::ostream& 
 */
std::ostream& red(std::ostream& s);

/**
 * @brief Fonction green, permet d'afficher du texte en vert.
 * 
 * @param s 
 * @return std::ostream& 
 */
std::ostream& green(std::ostream& s);

/**
 * @brief Fonction yellow, permet d'afficher du texte en jaune.
 * 
 * @param s 
 * @return std::ostream& 
 */
std::ostream& yellow(std::ostream& s);

/**
 * @brief Fonction reset, permet de réinitialiser la couleur du texte.
 * 
 * @param s 
 * @return std::ostream& 
 */
std::ostream& reset(std::ostream& s);


#endif // LOG_H