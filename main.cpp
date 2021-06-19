#include <iostream>
#include <string>
#include "./httplib.h"
const std::string form = R"(
<!DOCTYPE html>
<html>
<body>

<form action="/submit" method="post">
  <label for="mess">Message:</label><br>
  <input type="text" id="mess" name="mess" value=""><br>
  <input type="submit" value="Submit">

</form> 
</body>
</html>
)";

//void handleGet(const httplib::Request& request, httplib::Response& response) {
//  response.set_content(form, "text/html");
//}

// request.get_param_value("...")
// response.set_content(form, "text/plain")

int main(void) {
  httplib::Server svr;

  std::vector<std::string> URLS;
  int count = 0;

  std::string last_message = "None";
  //svr.Get("/", handleGet);
  svr.Get("/", [](const auto &, auto &response) {
    
    //response.set_content(bgstr, "text/plain");
    response.set_content(form, "text/html");
    //cout << &response << "\n";
  });

  svr.Get(R"(/(\d+))", [&](const httplib::Request& req, httplib::Response& res){
    auto ind = req.matches[1];
    std::cout << ind << "\n";
    res.status = 301;
    res.set_header("Location",URLS[std::stoi(ind)]);
    res.set_content(URLS[std::stoi(ind)],"text/html");
  });

  svr.Post("/submit", [&URLS](const auto & request, auto &response) {
    std::string url = request.get_param_value("mess");
    URLS.push_back(url);
    int ind = URLS.size()-1;
    std::string newURL = "https://requiredtemporalportablesoftware.tychoelling.repl.co/" + std::to_string(ind);
    response.set_content(newURL, "text/plain");
  });
  
  svr.listen("0.0.0.0", 8080);

    
  
  
}