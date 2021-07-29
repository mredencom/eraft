// MIT License

// Copyright (c) 2021 Colin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <Logger/Logger.h>
#include <string>

Logger* Logger::instance_ = nullptr;

std::string currTime()
{
    // 获取当前时间，并规范表示
    char tmp[64];
    time_t ptime;
    time(&ptime);  // time_t time (time_t* timer);
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&ptime));
    return tmp;
}

Logger::Logger()
{
    // 默认构造函数
    m_target = terminal;
    m_level = debug;
    std::cout << /*"[WELCOME] " << __FILE__ << " " <<*/ currTime() << " : " << "=== Start logging ===" << std::endl;
}

Logger::Logger(log_target target, log_level level, const std::string& path)
{
    m_target = target;
    m_path = path;
    m_level = level;

    std::string strContent =   currTime() + " : " + "=== Start logging ===\n";
    if (target != terminal) {
        m_outfile.open(path, std::ios::out | std::ios::app);   // 打开输出文件
        m_outfile << strContent;
    }
    if (target != file) 
    {
        // 如果日志对象不是仅文件
        std::cout << strContent;
    }
}

Logger::~Logger()
{
    std::string  strContent =  currTime() + " : " + "=== End logging ===\r\n";
    if (m_outfile.is_open())
    {
        m_outfile << strContent;
    }
    m_outfile.flush();
    m_outfile.close();
}


void Logger::DEBUG(const std::string& text)
{
    output(text, debug);
}

void Logger::DEBUG_NEW(const std::string& in, const std::string& file, uint64_t line, const std::string& function)
{
    std::string text;
    text.append(" [ ");
    text.append(file);
    text.append(":");
    text.append(std::to_string(line));
    text.append(" ]");
    text.append(" ");
    text.append(function);
    text.append(" [ ");
    text.append(std::string(in));
    text.append(" ]");
    output(text, debug);
}

void Logger::INFO(const std::string& text)
{
    output(text, info);
}

void Logger::WARNING(const std::string& text)
{
    output(text, warning);
}

void Logger::ERRORS(const std::string& text)
{
    output(text, error);
}

void Logger::output(const std::string &text, log_level act_level)
{
    std::string prefix;
    if (act_level == debug) prefix = "[DEBUG] ";
    else if (act_level == info) prefix = "[INFO] ";
    else if (act_level == warning) prefix = "[WARNING] ";
    else if (act_level == error) prefix = "[ERROR] ";
    //else prefix = "";
    // prefix += __FILE__;
    //prefix += " ";
    std::string outputContent = prefix + " " + currTime() + " : " + text + "\n";
    if (m_level <= act_level && m_target != file) 
    {
        // 当前等级设定的等级才会显示在终端，且不能是只文件模式
        std::cout << outputContent;
    }
    if (m_target != terminal)
        m_outfile << outputContent;

    m_outfile.flush();//刷新缓冲区
}
