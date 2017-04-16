/**
   @author Rafael Cisneros
 */

#include <cnoid/Plugin>

class WorkspaceDisplayerPlugin : public Plugin
{
public:

  WorkspaceDisplayerPlugin() : Plugin("WorkspaceDisplayer")
  {}
  
  virtual bool intialize()
  {
    return true;
  }

  virtual const char *description()
  {
    static std::string text = "This plug-in is being developed by Rafael Cisneros and is still under construction...";
    return text.c_str();
  }
};

CNOID_IMPLEMENT_PLUGIN_ENTRY(WorkspaceDisplayerPlugin)
