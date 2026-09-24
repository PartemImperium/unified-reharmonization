{
  description = "Harmony Hub Remote.";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs =
    {
      self,
      nixpkgs,
    }:
    let
      unified-reharmonization =
        {
          lib,
          stdenv,

          cmake,
          libusb1,
          pkg-config,
        }:

        stdenv.mkDerivation {
          pname = "unified-reharmonization";
          version = self.shortRev or self.dirtyShortRev or "unknown";

          src = ./Sniffer;

          nativeBuildInputs = [
            cmake
            pkg-config
            libusb1
          ];

          meta = {
            description = "";
            #homepage = "";
            #license = lib.licenses.gpl3Only;
            mainProgram = "unified-reharmonization";
            platforms = lib.platforms.linux;
          };
        };

      inherit (nixpkgs) lib;
      # Support all Linux systems that the nixpkgs flake exposes
      systems = lib.intersectLists lib.systems.flakeExposed lib.platforms.linux; 

      forAllSystems = lib.genAttrs systems;
      nixpkgsFor = forAllSystems (system: nixpkgs.legacyPackages.${system});
    in
    {
      packages = forAllSystems (
        system:
        {
          unified-reharmonization = nixpkgsFor.${system}.callPackage unified-reharmonization { };
        }
      );
    };
}
