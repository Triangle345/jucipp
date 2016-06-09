#ifndef JUCI_DEBUG_CLANG_H_
#define JUCI_DEBUG_CLANG_H_

#include <boost/filesystem.hpp>
#include <unordered_map>
#include <lldb/API/SBDebugger.h>
#include <lldb/API/SBListener.h>
#include <lldb/API/SBProcess.h>
#include <thread>
#include <mutex>

namespace Debug {
  class Clang {
  public:
    class Frame {
    public:
      uint32_t index;
      std::string module_filename;
      boost::filesystem::path file_path;
      std::string function_name;
      int line_nr;
      int line_index;
    };
    class Variable {
    public:
      uint32_t thread_index_id;
      uint32_t frame_index;
      std::string name;
      std::string value;
      boost::filesystem::path file_path;
      int line_nr;
      int line_index;
    };
  private:
    Clang();
  public:
    static Clang &get() {
      static Clang singleton;
      return singleton;
    }
    
    void start(const std::string &command, const boost::filesystem::path &path="",
               const std::vector<std::pair<boost::filesystem::path, int> > &breakpoints={},
               std::function<void(int exit_status)> callback=nullptr,
               std::function<void(const std::string &status)> status_callback=nullptr,
               std::function<void(const boost::filesystem::path &file_path, int line_nr, int line_index)> stop_callback=nullptr,
               const std::string &plugin="", const std::string &url="");
    void continue_debug(); //can't use continue as function name
    void stop();
    void kill();
    void step_over();
    void step_into();
    void step_out();
    std::pair<std::string, std::string> run_command(const std::string &command);
    std::vector<Frame> get_backtrace();
    std::vector<Variable> get_variables();
    void select_frame(uint32_t frame_index, uint32_t thread_index_id=0);
    
    void cancel();
    
    std::string get_value(const std::string &variable, const boost::filesystem::path &file_path, unsigned int line_nr, unsigned int line_index);
    std::string get_return_value(const boost::filesystem::path &file_path, unsigned int line_nr, unsigned int line_index);
    
    bool is_invalid();
    bool is_stopped();
    bool is_running();
    
    void add_breakpoint(const boost::filesystem::path &file_path, int line_nr);
    void remove_breakpoint(const boost::filesystem::path &file_path, int line_nr, int line_count);
    
    void write(const std::string &buffer);
    
    static std::vector<std::string> get_platform_list();
      
  private:
    std::unique_ptr<lldb::SBDebugger> debugger;
    std::unique_ptr<lldb::SBListener> listener;
    std::unique_ptr<lldb::SBProcess> process;
    std::thread debug_thread;
    
    lldb::StateType state;
    std::mutex event_mutex;
    
    size_t buffer_size;
  };
}

#endif
