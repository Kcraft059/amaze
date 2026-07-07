{ pkgs, ... }:
{
  default = pkgs.mkShell {
    packages =
      with pkgs;
      [
        gnumake
        ncurses
      ]
      ++ (if pkgs.stdenv.isLinux then [ gcc ] else [ clang ]);

    shellHook = ''
      if command -v >/dev/null zsh; then
        exec zsh --rcs -i -c "zsh -i"
      fi
    '';
  };
}
