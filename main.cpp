#include <iostream>
#include <string>
#include "./httplib.h"
using namespace std;
const std::string form = R"(
<!DOCTYPE html>
<html>
<body>

<form action="/submit" method="post">
  <label for="mess">Message:</label><br>
  <input type="text" id="mess" name="mess" value=""><br>
  <input type="submit" value="Submit">

</form> 
<p>xxx</p>
<p>yyy</p>
zzz
<br/>
www
<br/>
</body>
</html>
)";

void handleGet(const httplib::Request& request, httplib::Response& response) {
  response.set_content(form, "text/html");
}

int main(void) {
  vector<string> v = {};
  httplib::Server svr;

  int count = 0;

  std::string last_message = "None";
  //svr.Get("/", handleGet);
  
  svr.Get("/", [&last_message,&v](const auto &, auto &response) {
    string bgstr = "";
    for (int i = v.size()-1; i > -1; i -= 1) {
      bgstr += v[i];
      bgstr += "\n";
    }
    //response.set_content(bgstr, "text/plain");
    response.set_content(form, "text/html");
    //cout << &response << "\n";
  });

  svr.Post("/submit", [&v](const auto & request, auto &response) {

    cout << request.get_param_value("mess") << "\n";
    v.push_back(request.get_param_value("mess"));
    string bgstr = "";
    for (int i = v.size()-1; i > -1; i -= 1) {
      bgstr += v[i];
      bgstr += "\n";
    }
    bgstr += request.get_param_value("mess");
    bgstr += "\n";
    response.set_content(bgstr, "text/plain");
  });
  
  svr.listen("0.0.0.0", 8080);

    
  
  
}