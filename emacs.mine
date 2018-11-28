
(defun up-slightly() (interactive) (scroll-up 3))
(global-set-key [mouse-5] 'up-slightly)
(defun dn-slightly() (interactive) (scroll-down 3))
(global-set-key [mouse-4] 'dn-slightly)


;; when selected, typing anything replaces the selection
(delete-selection-mode 1)

(global-set-key "\M-g" 'goto-line)

;; get rid of keys which cause accidental exiting
(global-unset-key "\C-z")
(global-unset-key "\C-x\C-z")
(global-unset-key "\C-x\C-c")
(global-set-key "\C-x\C-c" 'close-nicely)
(defun close-nicely ()
  "Ask before closing even if no changes"
  (interactive)
  (if (y-or-n-p (format "Are you sure you want to exit?"))
      (save-buffers-kill-emacs)
    (message "Exiting cancelled")))

;; press  key when on a parenthesis to find its match
(global-set-key "%" 'match-paren)
(defun match-paren (arg)
  (interactive "p")
  (cond ((looking-at "\\s\(") (forward-list 1) (backward-char 1))
	((looking-at "\\s\)") (forward-char 1) (backward-list 1))
	(t (self-insert-command (or arg 1)))
	)
  )

;; do not add the undos to the undo list
(global-set-key "\C-x\C-u" 'undo-only)

;; Customizations for all modes in CC Mode.
;; see emacs cc-mode info pages in the help menu
(defun my-c-mode-common-hook ()
  (setq indent-tabs-mode nil) ;; spaces over tabs!!
  ;; indentation 
  (setq c-tab-always-indent t) ;; indent from any position
  (setq c-basic-offset 4)
  (c-set-offset 'substatement-open '0)	;; do not indent inline braces
  (c-set-offset 'arglist-intro '+)	;; do not align arglist to the '('
  
  (c-set-offset 'access-label '/) ;; move public/protected etc half back
  (c-set-offset 'statement-case-intro '*) ;; indent case statements by half
  (c-set-offset 'case-label '*)
  ;; Turns on (simulates) auto indentation for all cc-modes
  (define-key c-mode-base-map "\C-m" 'newline-and-indent)
  
  )

(add-hook 'c-mode-common-hook 'my-c-mode-common-hook 'append)

(defun revert-all-buffers ()
  "Revert all modified buffers"
  (interactive)
  (dolist (buf (buffer-list))
    (let ((filename (buffer-file-name buf)))
      ;; Revert only buffers containing files, which are modified;
      ;; do not try to revert non-file buffers like *Messages*.
      (when (and filename
		 (buffer-modified-p buf)) ;; check if buffer is modified
;;	(message "Reverting 's' 
	(with-current-buffer buf
	  (revert-buffer :ignore-auto :noconfirm :preserve-modes))
          )))
  (message "Finished reverting buffers containing unmodified files."))
