require "sinatra/activerecord"

class Keg < ActiveRecord::Base
  
  has_many :measurements

  def self.get_data(sp)
    while true do 
      sp_char = sp.getc

      if sp_char && sp_char.start_with?("pulses:")
        number = sp_char.split(":")[1]
        puts number
      end
    end
  end



end





