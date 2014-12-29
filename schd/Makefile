include $(TOPDIR)/rules.mk

PKG_NAME:=schd
PKG_VERSION:=0.0.1
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Charles Teng <charles_teng@cameo.com.tw>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Build/Prepare
	$(INSTALL_DIR) $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/schd
  SECTION:=schd
  CATEGORY:=Base system
  DEFAULT:=y
  TITLE:=Extra filesystem for OpenWrt(schedule)
  DEPENDS:=+ubusd +ubus +libjson-script +ubox +USE_EGLIBC:librt +libubox +libubus
endef

define Package/schd/description
 This package contains a extra filesystem and system scripts for OpenWrt(schedule).
endef

#define Build/Configure
#endef

#define Build/Compile
#	$(MAKE) -C $(PKG_BUILD_DIR) \
#		CC="$(TARGET_CC) -fPIC" \
#		CFLAGS="$(TARGET_CFLAGS) -Wall" \
#		LDFLAGS="$(TARGET_LDFLAGS)"
#endef

#define Build/InstallDev
#endef

define Package/schd/install
#	$(CP) $(PKG_BUILD_DIR)/files/* $(1)/
	$(INSTALL_DIR) $(1)/sbin 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/schd $(1)/sbin/
	$(INSTALL_DIR) $(1)/etc/config 
	$(CP) ./files/etc/config/* $(1)/etc/config/
# build package
#	$(MAKE) -C $(PKG_BUILD_DIR) INSTALLDIR=$(1) install STRIP="mips-openwrt-linux-uclibc-strip"
#	$(MAKE) -C $(PKG_BUILD_DIR) INSTALLDIR=$(1) install STRIP="mips-openwrt-linux-uclibc-strip"
endef

$(eval $(call BuildPackage,schd))
