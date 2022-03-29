#!/usr/bin/perl -w

$ip			= "127.0.0.1";
$port		= 8000;
$password	= "pswd";

use Irssi;

Irssi::print("*** Ircredible tester ***\n");


#connect test - le sleep ne semble pas bien fonctionner

# $i = 0;
# while ($i < 10)
# {
# 	Irssi::print("connect  n: $i");

# 	Irssi::command("connect $ip $port $password");
#     sleep(1);
# 	Irssi::command("disconnect");
#     Irssi::print("\n");

# 	Irssi::command("rmreconns");
# 	$i++;
# }

 sub event_privmsg {
    # $data = "nick/#channel :text"
    my ($server, $data, $nick, $address) = @_;
    my ($target, $text) = split(/ :/, $data, 2);

    Irssi::signal_stop() if ($text =~ /free.*porn/ || $nick =~ /idiot/);
  }

Irssi::signal_add("event privmsg", "event_privmsg")


# nick test

# Irssi::print("** nick test **\n\n");
# Irssi::print("connect :\n");
# $server->command("connect $ip $port $password");
# Irssi::command("connect $ip $port $password");
# Irssi::sleep(2);

# Irssi::print("\nwhois :\n");
# Irssi::command("whois");

# Irssi::print("\nnick billybob ->\n");
# Irssi::print("\nwhois :\n");
# Irssi::command("whois");



