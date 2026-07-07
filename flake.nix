{
  description = "Amaze game flake & dev environnement";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";
  };

  outputs =
    { nixpkgs, ... }:
    let
      forAllSystems =
        subset:
        (nixpkgs.lib.genAttrs [
          "aarch64-darwin"
          "x86_64-darwin"
          "aarch64-linux"
          "x86_64-linux"
        ])
          (
            system:
            let
              pkgs = import nixpkgs { inherit system; };
            in
            subset { inherit system pkgs; }
          );
    in
    {
      packages = forAllSystems ({ pkgs, system }: (import ./package.nix { inherit system pkgs; }));
      devShells = forAllSystems ({ pkgs, system }: (import ./shell.nix { inherit system pkgs; }));
    };
}
