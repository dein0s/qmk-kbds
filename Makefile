QMK_LOCAL=$(CURDIR)/qmk_firmware
ORIGINAL_QMK_HOME := $(shell qmk config -ro user | grep 'user.qmk_home' | cut -d '=' -f 2)

USER = dein0s

KEYBOARDS = k_q11 k_q1v2
PATH_k_q11 = keychron/q11/ansi_encoder
PATH_k_q1v2 = keychron/q1v2/ansi_encoder
# /keyboards/keebio/iris

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):
# init submodule
	git submodule update --init --recursive
	git submodule update --remote
	# set qmk to current dir
	qmk config user.qmk_home="$(QMK_LOCAL)"
	# cleanup old symlinks
	rm -rf $(CURDIR)/qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)
	# rm -rf $(CURDIR)/qmk_firmware/keyboards/keychron/q1v2
	# add new symlinks
	# ln -s $(CURDIR)/k_q1v2_orig $(QMK_LOCAL)/keyboards/keychron/q1v2
	ln -s $(CURDIR)/$@ $(QMK_LOCAL)/keyboards/$(PATH_$@)/keymaps/$(USER)
	# qmk lint
	qmk lint -km $(USER) -km $(USER) -kb $(PATH_$@)
	# run build
	make BUILD_DIR=$(CURDIR)/.build -j1 -C qmk_firmware $(PATH_$@):$(USER)
	# reset qmk to what it was before
	qmk config user.qmk_home="$(ORIGINAL_QMK_HOME)"
	rm -rf $(CURDIR)/qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)

clean:
	# rm -rf $(CURDIR)/qmk_firmware/keyboards/keychron/q1v2
	rm -rf $(CURDIR)/.build/
