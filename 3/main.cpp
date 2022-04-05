#include <iostream>
#include <cpr/cpr.h>
#include <map>

static void coutHeaders(const cpr::Header &h);

int main()
{
  std::map<std::string, std::string> args;
  std::string key;
  do
  {
    std::cin >> key;
    if (key == "post" || key == "get")
      continue;
    std::string val;
    std::cin >> std::ws;
    std::getline(std::cin, val);
    args.insert(std::make_pair(key, val));
  }while (key != "post" && key != "get");

  cpr::Response r;
  if (key == "post")
  {
    std::vector<cpr::Pair> argsVector;
    for (std::map<std::string, std::string>::iterator it = args.begin(); it != args.end(); it++)
      argsVector.push_back(cpr::Pair(it->first, it->second));
    cpr::Payload payload(argsVector.begin(), argsVector.end());
    r = cpr::Post(cpr::Url("http://httpbin.org/post"), payload);
    coutHeaders(r.header);
    std::cout << r.text << std::endl;
  }
  else
  {
    std::string url = "http://httpbin.org/get";
    if (!args.empty())
    {
      for (std::map<std::string, std::string>::iterator it = args.begin(); it != args.end(); it++)
        url += (it == args.begin() ? "?":"&") + it->first + "=" + it->second;
      r = cpr::Get(cpr::Url(url));
      coutHeaders(r.header);
      std::cout << r.text << std::endl;
    }
  }
  return 0;
}

static void coutHeaders(const cpr::Header &h)
{
  for(cpr::Header::const_iterator it = h.cbegin(); it != h.cend(); it++ )
    std::cout << it->first << ": " << it->second << std::endl;
}