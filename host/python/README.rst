===============================
arduino_relay_remote_controller
===============================

arduino_relay_remote_controller is a python package to control the
Arduino relay remote controller over USB, using the python module, the
command line, or a webpage using a webserver.


Install
-------

See INSTALL.rst

Python Module
-------------

If installed into a python virtual environment, first activate it::

    source ~/virtualenvs/arduino_relay_remote_controller/bin/activate

Use ipython to run or test::

    ipython

Typical usage from an ipython shell often looks like this::

    from arduino_relay_remote_controller import ArduinoRelayRemoteController, ArduinoRelayRemoteControllers

    relay_remote_controllers = ArduinoRelayRemoteControllers()
    device_count = len(relay_remote_controllers)
    if device_count == 0:
        raise RuntimeError('No Arduino relay remote controllers detected, check connections.')
    relay_remote_controllers[0].getDevInfo()

    rrc = relay_remote_controllers[0]
    rrc.getCmds()
    # turn on all relays
    rrc.setAllRelaysOn()
    # turn off all relays
    rrc.setAllRelaysOff()
    # turn on relay 12
    rrc.setRelayOn(12)
    # turn off relay 12
    rrc.setRelayOff(12)
    # turn all board 0 relays on
    rrc.setAllBoardRelaysOn(0)
    # turn all board 0 relays off
    rrc.setAllBoardRelaysOff(0)
    # turn on relay 2 on board 1
    rrc.setBoardRelayOn(1,2)
    # turn on relay 2 on board 1
    rrc.setBoardRelayOff(1,2)


Web Page Controls
-----------------

Open a terminal and run::

    arduino_relay_remote_controller_webserver.py

Open a browser and navigate to::

    http://localhost:5000


Author: Peter Polidoro

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
