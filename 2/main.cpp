#include <iostream>
#include <cpr/cpr.h>
#include <string>

std::string parseTag(const std::string &text, const std::string &t);

int main()
{
  cpr::Response r;
  r = cpr::Get(cpr::Url("http://httpbin.org/html"),
     cpr::Header({{"accept", "text/html"}}));
  std::cout << parseTag(r.text, "h1") << std::endl;
  return 0;
}

std::string parseTag(const std::string &text, const std::string &t)
{
  std::string ret = "";
  std::string openTag = "<" + t + ">";
  std::string closeTag = "</" + t + ">";

  size_t openPos = text.find(openTag);
  size_t closePos = std::string::npos;
  if (std::string::npos != openPos)
  {
    openPos += openTag.size();
    closePos = text.find(closeTag, openPos);
  }
  if (std::string::npos != openPos && std::string::npos != closePos)
    ret = text.substr(openPos, closePos - openPos);
  return ret;
}