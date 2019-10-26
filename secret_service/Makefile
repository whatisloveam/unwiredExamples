# name of your application
APPLICATION = secret_service

# If no BOARD is found in the environment, use this default:
BOARD ?= unwd-range-l1-r3

USEMODULE += xtimer
FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_timer
USEMODULE += periph_gpio_irq
# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= /home/student/Melnikow/riot_unwds

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1



# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1





include $(RIOTBASE)/Makefile.include
