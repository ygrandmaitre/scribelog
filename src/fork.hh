/**
 ** \file fork.hh
 ** \brief Declaration of Fork.
 */

#ifndef FORK_HH
# define FORK_HH

# include <unistd.h>

# include <list>

/** \brief Define \c Fork class.
   **
   ** A very simple C++ wrapper for the fork command.
   */
class Fork
{
public:
  /** \name Ctor & Dtor.
   ** \{ */
  /** \brief Construct a \c Fork. */
  Fork ();
  /** \brief Destructor a \c Fork. */
  ~Fork ();
  /** \} */

  /** \name Accessors.
   ** \{ */
  /// Return the pid.
  pid_t pid_get () const;

  /**
   *  Test whether we are in parent section of the code.
   *  Return true if it is parent code, false otherwise.
   */
  bool is_parent () const;

  /**
   *  Test whether we are in child section of the code.
   *  Return true if it is child code, false otherwise.
   */
  bool is_child () const;

  /**
   *  Execute an external command.
   *  Conveniently wraps fork()/execvp()/wait() sequence of calls.
   *
   *  @param cmd_                 Command to execute.
   *  @param list_argv            Arguments list.
   *  @param wait_child  If set to true, blocks until child exits;
   *                               false otherwise.
   *
   *  @return If wait_for_completion_ is false, returns child PID;
   *          If wait_for_completion_ is true, returns command exit status.
   */
  static int fork_exec (const std::string& cmd,
                        std::list<std::string>& list_argv,
                        bool wait_child = true);

private:
  /// pid
  pid_t pid_;
};

# include "fork.hxx"

#endif // !FORK_HH
