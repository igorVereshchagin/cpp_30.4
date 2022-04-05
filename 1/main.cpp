#include <iostream>
#include <string>
#include <cpr/cpr.h>

void httpGet();
void httpPost();
void httpPut();
void httpDelete();
void httpPatch();

static void coutHeaders(const cpr::Header &h);

int main()
{
  std::string cmd;
  do
  {
    std::cin >> cmd;
    if ("get" == cmd)
    {
      httpGet();
    }
    else if ("post" == cmd)
    {
      httpPost();
    }
    else if ("put" == cmd)
    {
      httpPut();
    }
    else if ("delete" == cmd)
    {
      httpDelete();
    }
    else if ("patch" == cmd)
    {
      httpPatch();
    }
  }while ("exit" != cmd);
  return 0;
}

void httpGet()
{
  cpr::Response r;
  r = cpr::Get(cpr::Url("http://httpbin.org/get"));
  coutHeaders(r.header);
  std::cout << r.text << std::endl;
}
void httpPost()
{
  cpr::Response r;
  std::string name = "Igor";
  std::string city = "Moscow";
  r = cpr::Post(cpr::Url("http://httpbin.org/post"),
                cpr::Payload({{"name", name}, {"city", city}}));
  coutHeaders(r.header);
  std::cout << r.text << std::endl;
}
void httpPut()
{
  cpr::Response r;
  r = cpr::Put(cpr::Url("http://httpbin.org/put"));
  coutHeaders(r.header);
  std::cout << r.text << std::endl;
}
void httpDelete()
{
  cpr::Response r;
  r = cpr::Delete(cpr::Url("http://httpbin.org/delete"));
  coutHeaders(r.header);
  std::cout << r.text << std::endl;
}
void httpPatch()
{
  cpr::Response r;
  r = cpr::Patch(cpr::Url("http://httpbin.org/patch"));
  coutHeaders(r.header);
  std::cout << r.text << std::endl;
}

static void coutHeaders(const cpr::Header &h)
{
  for(cpr::Header::const_iterator it = h.cbegin(); it != h.cend(); it++ )
    std::cout << it->first << ": " << it->second << std::endl;
}