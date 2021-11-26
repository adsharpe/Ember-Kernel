# Ember-Kernel
A new kernel for PyroOS.

## About
The Ember Kernel is a replacement kernel for the [Pyro Operating System](http://pyro-os.org/). It is meant to be completely compatible with the Pyro OS system call interface, while supassing the original kernel in features and performance. The original kernel was inheritted from Syllable, which modified the kernel that it inheritted from AtheOS.

## Planned Features
* Grub2 booting
* X86_64 - fully 64-bit, with no 32-bit support
* Excecutable space protection - NX bit
* Atomic primitives
* Synchonization primatives
* Memory protection
* Fully pre-emptive, multi-hreaded scheduling
* Object management
* Virtual memory management - M:N memory mapping
* Process/Thread management
* Dynamic module management
* Event management
* VFS/Vnode management
* Network protocol management
* Dynamically generated /dev filesystem
* Pseudo-device managers (busses, services, etc.)
* Kernel console
* Kernel debugger
* System call interface
* Graphical loading screen
* AtheOS FS driver

## Author
*  **Apollo D. Sharpe, Sr.** - [adsharpe](https://github.com/adsharpe)

## License
The Ember Kernel is licensed under the CDDL License.