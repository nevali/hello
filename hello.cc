#include <iostream>

int 
main(void)
{
	/* std::cout is a stream object bound to the 'standard output' file
	 * descriptor, which is where your normal output should be sent.
	 *
	 * Standard C++ stream objects override the << operator to provide a
	 * convenient syntax for writing to them.
	 */
	std::cout << "Hello, world!" << std::endl;
	
	/* The return value of main() is used as the program's exit status, which can
	 * be retrieved and checked by whatever program or script invoked yours: zero
	 * means it ran successfully, non-zero values mean an error occurred. It's up
	 * to you to define what those error codes might be used for. On many systems,
	 * negative exit statuses and values greater than 127 aren't guaranteed to
	 * work properly.
	 */
	return 0;
}
