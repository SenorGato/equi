Kill Timers:
Recieve new line
if $LINE = "There are # players in (.*)" then
    $ZONE = (.*)
if $LINE = "You have slain *" then
if !$ZONE then "Please capture zone" && capture zone
if !$RESPAWN search db for zone respawn, and set $RESPAWN
set timer for $RESPAWN for (mob)
if $timer = 0 then event


Potential Windows:

    Splits
    Buff Timers
    Mob Timers
    Plat Counter
    Kill counter
    Terminal Output
    Notes
    Drop rates
